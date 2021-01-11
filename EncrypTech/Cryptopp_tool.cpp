#include "Cryptopp_tool.h"
// �����ļ��� SHA1 ֵ
string CalSHA1_ByFile(const char* pszFileName)
{
	string value;
	SHA1 sha1;
	FileSource(pszFileName, true, new HashFilter(sha1, new HexEncoder(new StringSink(value))));
	return value;
}


// �������ݵ� SHA1 ֵ
string CalSHA1_ByMem(PBYTE pData, DWORD dwDataSize)
{
	string value;
	SHA1 sha1;
	StringSource(pData, dwDataSize, true, new HashFilter(sha1, new HexEncoder(new StringSink(value))));
	return value;
}

// �����ļ��� SHA256 ֵ
string CalSHA256_ByFile(const char* pszFileName)
{
	string value;
	SHA256 sha256;
	FileSource(pszFileName, true, new HashFilter(sha256, new HexEncoder(new StringSink(value))));
	return value;
}


// �������ݵ� SHA256 ֵ
string CalSHA256_ByMem(PBYTE pData, DWORD dwDataSize)
{
	string value;
	SHA256 sha256;
	StringSource(pData, dwDataSize, true, new HashFilter(sha256, new HexEncoder(new StringSink(value))));
	return value;
}

// �����ļ��� MD5 ֵ
string CalMD5_ByFile(const char* pszFileName)
{
	string value;
	MD5 md5;
	FileSource(pszFileName, true, new HashFilter(md5, new HexEncoder(new StringSink(value))));
	return value;
}


// �������ݵ� MD5 ֵ
string CalMD5_ByMem(PBYTE pData, DWORD dwDataSize)
{
	string value;
	MD5 md5;
	StringSource(pData, dwDataSize, true, new HashFilter(md5, new HexEncoder(new StringSink(value))));
	return value;
}

// ��Կ����
// �����AES��Կ��AES��Կ����
BOOL GenerateAESKey(BYTE* pAESKey, DWORD* pdwAESKeyLength, DWORD dwBufferSize)
{
	srand(time(NULL));

	if (AES::MIN_KEYLENGTH > *pdwAESKeyLength)
	{
		*pdwAESKeyLength = AES::MIN_KEYLENGTH;
	}
	else if (AES::MAX_KEYLENGTH < *pdwAESKeyLength)
	{
		*pdwAESKeyLength = AES::MAX_KEYLENGTH;
	}


	// ��Կ���ȴ��ڻ�����
	if (dwBufferSize < *pdwAESKeyLength)
	{
		return FALSE;
	}

	// ���������Կ(��Сд��ĸ�����֡��ַ��ȿ���ʾ�ַ�)
	// 33 - 126
	int i = 0;
	::RtlZeroMemory(pAESKey, dwBufferSize);
	for (i = 0; i < *pdwAESKeyLength; i++)
	{
		pAESKey[i] = 33 + (rand() % 94);
	}

	return TRUE;
}


// ����
// ���룺ԭ�����ݡ�ԭ�����ݳ��ȡ���Կ���ݡ���Կ���ݳ���
// ������������ݡ��������ݳ���
BOOL AES_Encrypt(BYTE* pOriginalData, DWORD dwOriginalDataSize, BYTE* pAESKey, DWORD dwAESKeySize, BYTE** ppEncryptData, DWORD* pdwEncryptData)
{
	// ������
	AESEncryption aesEncryptor;
	// ����ԭ�����ݿ�
	unsigned char inBlock[AES::BLOCKSIZE];
	// ���ܺ��������ݿ�
	unsigned char outBlock[AES::BLOCKSIZE];
	// �����趨ȫΪ0
	unsigned char xorBlock[AES::BLOCKSIZE];

	DWORD dwOffset = 0;
	BYTE* pEncryptData = NULL;
	DWORD dwEncryptDataSize = 0;

	// ����ԭ�ĳ���, ���� 128λ �� 16�ֽ� ����, ������ ���0 ����
	// ��
	DWORD dwQuotient = dwOriginalDataSize / AES::BLOCKSIZE;
	// ����
	DWORD dwRemaind = dwOriginalDataSize % AES::BLOCKSIZE;
	if (0 != dwRemaind)
	{
		dwQuotient++;
	}

	// ���붯̬�ڴ�
	dwEncryptDataSize = dwQuotient * AES::BLOCKSIZE;
	pEncryptData = new BYTE[dwEncryptDataSize];
	if (NULL == pEncryptData)
	{
		return FALSE;
	}

	// ������Կ
	aesEncryptor.SetKey(pAESKey, dwAESKeySize);

	do
	{
		// ����
		::RtlZeroMemory(inBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(xorBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(outBlock, AES::BLOCKSIZE);

		// ��ȡ���ܿ�
		if (dwOffset <= (dwOriginalDataSize - AES::BLOCKSIZE))
		{
			::RtlCopyMemory(inBlock, (PVOID)(pOriginalData + dwOffset), AES::BLOCKSIZE);
		}
		else
		{
			::RtlCopyMemory(inBlock, (PVOID)(pOriginalData + dwOffset), (dwOriginalDataSize - dwOffset));
		}

		// ����
		aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);

		// ����
		::RtlCopyMemory((PVOID)(pEncryptData + dwOffset), outBlock, AES::BLOCKSIZE);

		// ��������
		dwOffset = dwOffset + AES::BLOCKSIZE;
		dwQuotient--;
	} while (0 < dwQuotient);

	// ��������
	*ppEncryptData = pEncryptData;
	*pdwEncryptData = dwEncryptDataSize;

	return TRUE;
}


// ����
// ���룺�������ݡ��������ݳ��ȡ���Կ���ݡ���Կ���ݳ���
// ��������ܺ��������ݡ����ܺ��������ݳ���
BOOL AES_Decrypt(BYTE* pEncryptData, DWORD dwEncryptData, BYTE* pAESKey, DWORD dwAESKeySize, BYTE** ppDecryptData, DWORD* pdwDecryptData)
{
	// ������
	AESDecryption aesDecryptor;
	// �����������ݿ�
	unsigned char inBlock[AES::BLOCKSIZE];
	// ���ܺ���������ݿ�
	unsigned char outBlock[AES::BLOCKSIZE];
	// �����趨ȫΪ0
	unsigned char xorBlock[AES::BLOCKSIZE];
	DWORD dwOffset = 0;
	BYTE* pDecryptData = NULL;
	DWORD dwDecryptDataSize = 0;

	// �������ĳ���, ���� 128λ �� 16�ֽ� ����, ���������0����
	// ��
	DWORD dwQuotient = dwEncryptData / AES::BLOCKSIZE;
	// ����
	DWORD dwRemaind = dwEncryptData % AES::BLOCKSIZE;
	if (0 != dwRemaind)
	{
		dwQuotient++;
	}

	// ���붯̬�ڴ�
	dwDecryptDataSize = dwQuotient * AES::BLOCKSIZE;
	pDecryptData = new BYTE[dwDecryptDataSize];
	if (NULL == pDecryptData)
	{
		return FALSE;
	}

	// ������Կ
	aesDecryptor.SetKey(pAESKey, dwAESKeySize);

	do
	{
		// ����
		::RtlZeroMemory(inBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(xorBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(outBlock, AES::BLOCKSIZE);

		// ��ȡ���ܿ�
		if (dwOffset <= (dwDecryptDataSize - AES::BLOCKSIZE))
		{
			::RtlCopyMemory(inBlock, (PVOID)(pEncryptData + dwOffset), AES::BLOCKSIZE);
		}
		else
		{
			::RtlCopyMemory(inBlock, (PVOID)(pEncryptData + dwOffset), (dwEncryptData - dwOffset));
		}

		// ����
		aesDecryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);

		// ����
		::RtlCopyMemory((PVOID)(pDecryptData + dwOffset), outBlock, AES::BLOCKSIZE);

		// ��������
		dwOffset = dwOffset + AES::BLOCKSIZE;
		dwQuotient--;
	} while (0 < dwQuotient);

	// ��������
	*ppDecryptData = pDecryptData;
	*pdwDecryptData = dwDecryptDataSize;

	return TRUE;
}


// ��ʾ����
// ���룺����������ݡ�����������ݳ���
void ShowData(BYTE* pData, DWORD dwSize)
{
	for (int i = 0; i < dwSize; i++)
	{
		if ((0 != i) &&
			(0 == i % 16))
		{
			printf("\n");
		}
		else if ((0 != i) &&
			(0 == i % 8))
		{
			printf(" ");
		}

		printf("%02X ", pData[i]);
	}
	printf("\n");
}


// ����RSA��Կ��
/*
	����void GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed, DWORD dwSeedLength)������������Կ�͹�Կ�ļ�.
	����keyLength����Կ����, PrivFilename�Ǵ����Կ���ļ���, pubFilename�Ǵ�Ź�Կ���ļ���, seedʱ������Կ������, dwSeedLength��seedʱ������Կ�����ӳ���.
	�ú���:
	1. ��������RandomPool�ķ���Put()��������seed��byte��α�����;
	2. RSAES_OAEP_SHA_Decryptor��һ�����ܵĹ�Կ����ϵͳ���ļ�rsa.h �����¶��壺
	   typedef RSAES<OAEP<SHA> >::Decryptor RSAES_OAEP_SHA_Decryptor; �������������ǰ�������α���������Կ����keyLength�����ܵ���Կ;
	3. Ȼ��ͨ����FileSink���ļ�szPrivateKeyFileNameʵ�����л���������HexEncoder����ת��Ϊʮ������;
	4. ����÷���DEREncode()�����洦��õ��������д���ļ�.
	�����͵õ�˽Կ�������Կ�ļ��ˡ�
	������Կ�ļ��ķ����Ͳ���˽Կ��Կ�ļ���ͬ�ĵط�����ʹ����RSAES_OAEP_SHA_Encryptor��һ�����ܵĹ�Կ����ϵͳ, ���ļ�rsa.h �����¶��壺
	typedef RSAES<OAEP<SHA> >::Encryptor RSAES_OAEP_SHA_Encryptor; ���������������Կ����ϵͳpriv��������Ӧ��Կ.
*/
BOOL GenerateRSAKey(DWORD dwRSAKeyLength, char* pszPrivateKeyFileName, char* pszPublicKeyFileName, BYTE* pSeed, DWORD dwSeedLength)
{
	RandomPool randPool;
	//randPool.Put(pSeed, dwSeedLength);
	randPool.IncorporateEntropy(pSeed, dwSeedLength);//�߰汾api�б䶯

	// ����RSA˽Կ
	RSAES_OAEP_SHA_Decryptor priv(randPool, dwRSAKeyLength);
	HexEncoder privFile(new FileSink(pszPrivateKeyFileName));	// ���ļ�ʵ�����л�����

	//priv.DEREncode(privFile);
	priv.AccessMaterial().Save(privFile);
	privFile.MessageEnd();

	// ����RSA��Կ
	RSAES_OAEP_SHA_Encryptor pub(priv);
	HexEncoder pubFile(new FileSink(pszPublicKeyFileName));		// ���ļ�ʵ�����л�����

	//pub.DEREncode(pubFile);										// д�������pub���ļ�����pubFile��
	priv.AccessMaterial().Save(privFile);
	pubFile.MessageEnd();

	return TRUE;
}


// RSA�����ַ���
/*
	���ܺ���string RSA_Encrypt(char *pszOriginaString, char *pszPublicKeyFileName, BYTE *pSeed, DWORD dwSeedLength) ��pszPublicKeyFileName�ǹ�Կ�ļ���pSeed�Ǽ������ӣ�pszOriginaString��Ҫ���ܵ��ַ�����
	��������Ļ��������ǣ�
	1. ��������RandomPool������seed���÷���Put()����α�������Seed������ȡ;;
	2. ����FileSource�Թ�Կ�ļ�pubFilename����һ����ת��������ʱ����������������ʮ������ת��Ϊbyte��;
	3. Ȼ����FileSource�Ķ���pubFile ʵ������Կ����ϵͳRSAES_OAEP_SHA_Encryptor���ɶ���pub;
	4. ����StringSink ��outstr��ӵ�һ��String���󣬽�����HexEncoder���������ת��Ϊʮ������;
	5. Ȼ����α�����randPool����Կ����ϵͳpub��ʮ�����Ƶ�String����ʵ����һ����Կ������ܵĹ�����������������������ַ���message���м��ܰѽ���ŵ�ʮ�����Ƶ��ַ���result�����������˶��ַ����ļ��ܡ�
*/
string RSA_Encrypt_ByFile(char* pszOriginaString, char* pszPublicKeyFileName, BYTE* pSeed, DWORD dwSeedLength)
{
	RandomPool randPool;
	randPool.IncorporateEntropy(pSeed, dwSeedLength);

	FileSource pubFile(pszPublicKeyFileName, TRUE, new HexDecoder);
	RSAES_OAEP_SHA_Encryptor pub(pubFile);

	// ����
	string strEncryptString;
	StringSource(pszOriginaString, TRUE, new PK_EncryptorFilter(randPool, pub, new HexEncoder(new StringSink(strEncryptString))));

	return strEncryptString;
}


// RSA�����ַ���
/*
	���ܺ����Ļ������̸����ܺ����Ļ������̲�࣬��ʹ���˼�����ͬ���࣬������Щ������ܺ����Ķ�Ӧ��Ĺ�������Եģ�������������ԾͲ�����Խ���
*/
string RSA_Decrypt_ByFile(char* pszEncryptString, char* pszPrivateKeyFileName)
{
	FileSource privFile(pszPrivateKeyFileName, TRUE, new HexDecoder);
	RSAES_OAEP_SHA_Decryptor priv(privFile);

	string strDecryptString;
	StringSource(pszEncryptString, TRUE, new HexDecoder(new PK_DecryptorFilter(GlobalRNG(), priv, new StringSink(strDecryptString))));

	return strDecryptString;
}


RandomPool& GlobalRNG()
{
	static RandomPool randomPool;

	return randomPool;
}


// RSA�����ַ���
string RSA_Encrypt_ByMem(char* pszOriginaString, char* pszMemPublicKey, BYTE* pSeed, DWORD dwSeedLength)
{
	RandomPool randPool;
	randPool.IncorporateEntropy(pSeed, dwSeedLength);

	StringSource pubStr(pszMemPublicKey, TRUE, new HexDecoder);
	RSAES_OAEP_SHA_Encryptor pub(pubStr);

	// ����
	string strEncryptString;
	StringSource(pszOriginaString, TRUE, new PK_EncryptorFilter(randPool, pub, new HexEncoder(new StringSink(strEncryptString))));

	return strEncryptString;
}


// RSA�����ַ���
string RSA_Decrypt_ByMem(char* pszEncryptString, char* pszMemPrivateKey)
{
	StringSource privStr(pszMemPrivateKey, TRUE, new HexDecoder);
	RSAES_OAEP_SHA_Decryptor priv(privStr);

	string strDecryptString;
	StringSource(pszEncryptString, TRUE, new HexDecoder(new PK_DecryptorFilter(GlobalRNG(), priv, new StringSink(strDecryptString))));

	return strDecryptString;
}