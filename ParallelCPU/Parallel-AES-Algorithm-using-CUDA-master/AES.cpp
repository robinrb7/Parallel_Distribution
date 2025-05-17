
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#define BYTE unsigned char

using namespace std;

class aes_block
{
public:
    BYTE block[16];
};

void printBytes(BYTE b[], int len) {
    int i;
    for (i=0; i<len; i++)
        printf("%x ", b[i]);
    printf("\n");
}

void f1printBytes(BYTE b[], int len, FILE* fp) {
    int i;
    for (i=0; i<len; i++)
        fprintf(fp, "%02x ", b[i]);
    fprintf(fp, "\n");
}

int flag=0;

void f2printBytes(BYTE b[], int len, FILE* fp) {
    int i;
    for (i=0; i<len; i++){
        fprintf(fp, "%c", b[i]);
        if(b[i]=='\n')
            flag++;
    }
}

void f3printBytes(BYTE b[], int len, FILE* fp) {
    int i;
    for (i=0; i<len; i++){
        if(b[i]=='\0'){
            return;
        }
        fprintf(fp, "%c", b[i]);
        if(b[i]=='\n')
            flag++;
    }
}

BYTE AES_Sbox[] =
{   /*0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f */
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76, /*0*/ 
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0, /*1*/
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15, /*2*/
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75, /*3*/
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84, /*4*/
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf, /*5*/
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8, /*6*/ 
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2, /*7*/
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73, /*8*/
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb, /*9*/
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79, /*a*/
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08, /*b*/
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a, /*c*/
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e, /*d*/
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf, /*e*/
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16  /*f*/
};

void AES_SubBytes(BYTE state[], BYTE sbox[]) {
    int i;
    for(i = 0; i < 16; i++)
        state[i] = sbox[state[i]];
}

void AES_AddRoundKey(BYTE state[], BYTE rkey[]) {
    int i;
    for(i = 0; i < 16; i++)
        state[i] ^= rkey[i];
}

void AES_ShiftRows(BYTE state[], BYTE shifttab[]) {
    BYTE h[16];
    memcpy(h, state, 16);
    int i;
    for(i = 0; i < 16; i++)
        state[i] = h[shifttab[i]];
}

void AES_MixColumns(BYTE state[], BYTE AES_xtime[]) {
    int i;
    for(i = 0; i < 16; i += 4) {
        BYTE s0 = state[i + 0], s1 = state[i + 1];
        BYTE s2 = state[i + 2], s3 = state[i + 3];
        BYTE h = s0 ^ s1 ^ s2 ^ s3;
        state[i + 0] ^= h ^ AES_xtime[s0 ^ s1];
        state[i + 1] ^= h ^ AES_xtime[s1 ^ s2];
        state[i + 2] ^= h ^ AES_xtime[s2 ^ s3];
        state[i + 3] ^= h ^ AES_xtime[s3 ^ s0];
    }
}

void AES_MixColumns_Inv(BYTE state[], BYTE AES_xtime[]) {
    int i;
    for(i = 0; i < 16; i += 4) {
        BYTE s0 = state[i + 0], s1 = state[i + 1];
        BYTE s2 = state[i + 2], s3 = state[i + 3];
        BYTE h = s0 ^ s1 ^ s2 ^ s3;
        BYTE xh = AES_xtime[h];
        BYTE h1 = AES_xtime[AES_xtime[xh ^ s0 ^ s2]] ^ h;
        BYTE h2 = AES_xtime[AES_xtime[xh ^ s1 ^ s3]] ^ h;
        state[i + 0] ^= h1 ^ AES_xtime[s0 ^ s1];
        state[i + 1] ^= h2 ^ AES_xtime[s1 ^ s2];
        state[i + 2] ^= h1 ^ AES_xtime[s2 ^ s3];
        state[i + 3] ^= h2 ^ AES_xtime[s3 ^ s0];
    }
}

void AES_Init(BYTE AES_Sbox[], BYTE AES_ShiftRowTab[], BYTE AES_Sbox_Inv[], BYTE AES_xtime[], BYTE AES_ShiftRowTab_Inv[]) {
    AES_ShiftRowTab[0]=0;
    AES_ShiftRowTab[1]=5;
    AES_ShiftRowTab[2]=10;
    AES_ShiftRowTab[3]=15;
    AES_ShiftRowTab[4]=4;
    AES_ShiftRowTab[5]=9;
    AES_ShiftRowTab[6]=14;
    AES_ShiftRowTab[7]=3;
    AES_ShiftRowTab[8]=8;
    AES_ShiftRowTab[9]=13;
    AES_ShiftRowTab[10]=2;
    AES_ShiftRowTab[11]=7;
    AES_ShiftRowTab[12]=12;
    AES_ShiftRowTab[13]=1;
    AES_ShiftRowTab[14]=6;
    AES_ShiftRowTab[15]=11;
    
    int i;
    for(i = 0; i < 256; i++){
        AES_Sbox_Inv[AES_Sbox[i]] = i;
    }
    for(i = 0; i < 16; i++)
        AES_ShiftRowTab_Inv[AES_ShiftRowTab[i]] = i;
    for(i = 0; i < 128; i++) {
        AES_xtime[i] = i << 1;
        AES_xtime[128 + i] = (i << 1) ^ 0x1b;
    }
}

void AES_Init2(BYTE AES_Sbox[], BYTE AES_ShiftRowTab[], BYTE AES_Sbox_Inv[], BYTE AES_xtime[], BYTE AES_ShiftRowTab_Inv[]) {
    AES_ShiftRowTab[0]=0;
    AES_ShiftRowTab[1]=5;
    AES_ShiftRowTab[2]=10;
    AES_ShiftRowTab[3]=15;
    AES_ShiftRowTab[4]=4;
    AES_ShiftRowTab[5]=9;
    AES_ShiftRowTab[6]=14;
    AES_ShiftRowTab[7]=3;
    AES_ShiftRowTab[8]=8;
    AES_ShiftRowTab[9]=13;
    AES_ShiftRowTab[10]=2;
    AES_ShiftRowTab[11]=7;
    AES_ShiftRowTab[12]=12;
    AES_ShiftRowTab[13]=1;
    AES_ShiftRowTab[14]=6;
    AES_ShiftRowTab[15]=11;
    
    int i;
    for(i = 0; i < 16; i++)
        AES_ShiftRowTab_Inv[AES_ShiftRowTab[i]] = i;
    for(i = 0; i < 128; i++) {
        AES_xtime[i] = i << 1;
        AES_xtime[128 + i] = (i << 1) ^ 0x1b;
    }
}

void AES_Done() {}

int AES_ExpandKey(BYTE key[], int keyLen) {
    int kl = keyLen, ks, Rcon = 1, i, j;
    BYTE temp[4], temp2[4];
    switch (kl) {
        case 16: ks = 16 * (10 + 1); break;
        case 24: ks = 16 * (12 + 1); break;
        case 32: ks = 16 * (14 + 1); break;
        default: 
        printf("AES_ExpandKey: Only key lengths of 16, 24 or 32 bytes allowed!");
    }
    for(i = kl; i < ks; i += 4) {
        memcpy(temp, &key[i-4], 4);
        if (i % kl == 0) {
            temp2[0] = AES_Sbox[temp[1]] ^ Rcon;
            temp2[1] = AES_Sbox[temp[2]];
            temp2[2] = AES_Sbox[temp[3]];
            temp2[3] = AES_Sbox[temp[0]];
            memcpy(temp, temp2, 4);
            if ((Rcon <<= 1) >= 256)
                Rcon ^= 0x11b;
        }
        else if ((kl > 24) && (i % kl == 16)) {
            temp2[0] = AES_Sbox[temp[0]];
            temp2[1] = AES_Sbox[temp[1]];
            temp2[2] = AES_Sbox[temp[2]];
            temp2[3] = AES_Sbox[temp[3]];
            memcpy(temp, temp2, 4);
        }
        for(j = 0; j < 4; j++)
            key[i + j] = key[i + j - kl] ^ temp[j];
    }
    return ks;
}

void AES_Encrypt(aes_block aes_block_array[], BYTE key[], int keyLen, int block_number) {
    BYTE AES_ShiftRowTab[16];
    BYTE AES_Sbox_Inv[256];
    BYTE AES_ShiftRowTab_Inv[16];
    BYTE AES_xtime[256];
    
    AES_Init(AES_Sbox, AES_ShiftRowTab, AES_Sbox_Inv, AES_xtime, AES_ShiftRowTab_Inv);
    
    for(int global_thread_index = 0; global_thread_index < block_number; global_thread_index++) {
        BYTE block[16]; 
        for(int i=0; i<16; i++){
            block[i] = aes_block_array[global_thread_index].block[i];
        }
        
        int l = keyLen, i;
        AES_AddRoundKey(block, &key[0]);
        for(i = 16; i < l - 16; i += 16) {
            AES_SubBytes(block, AES_Sbox);
            AES_ShiftRows(block, AES_ShiftRowTab);
            AES_MixColumns(block, AES_xtime);
            AES_AddRoundKey(block, &key[i]);
        }
        AES_SubBytes(block, AES_Sbox);
        AES_ShiftRows(block, AES_ShiftRowTab);
        AES_AddRoundKey(block, &key[i]);
        
        for(int i=0; i<16; i++){
            aes_block_array[global_thread_index].block[i] = block[i];
        }
    }
}

void AES_Decrypt(aes_block aes_block_array[], BYTE key[], int keyLen, int block_number) {
    BYTE AES_ShiftRowTab[16];
    BYTE AES_Sbox_Inv[256];
    BYTE AES_ShiftRowTab_Inv[16];
    BYTE AES_xtime[256];
    
    AES_Init2(AES_Sbox, AES_ShiftRowTab, AES_Sbox_Inv, AES_xtime, AES_ShiftRowTab_Inv);
    
    for(int global_thread_index = 0; global_thread_index < block_number; global_thread_index++) {
        BYTE block[16]; 
        for(int i=0; i<16; i++){
            block[i] = aes_block_array[global_thread_index].block[i];
        }
        
        int l = keyLen, i;
        AES_AddRoundKey(block, &key[l - 16]);
        AES_ShiftRows(block, AES_ShiftRowTab_Inv);
        AES_SubBytes(block, AES_Sbox_Inv);
        for(i = l - 32; i >= 16; i -= 16) {
            AES_AddRoundKey(block, &key[i]);
            AES_MixColumns_Inv(block, AES_xtime);
            AES_ShiftRows(block, AES_ShiftRowTab_Inv);
            AES_SubBytes(block, AES_Sbox_Inv);
        }
        AES_AddRoundKey(block, &key[0]);
        
        for(int i=0; i<16; i++){
            aes_block_array[global_thread_index].block[i] = block[i];
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream ifs;
    ifs.open(argv[1], std::ifstream::binary);
    if(!ifs){
        cerr<<"Cannot open the input file"<<endl;
        exit(1);
    }
    ifs.seekg(0, ios::end);
    int infileLength = ifs.tellg();
    ifs.seekg (0, ios::beg);
    cout<<"Length of input file: "<<infileLength<<endl;

    auto start = std::chrono::high_resolution_clock::now();

    int block_number = infileLength/16;
    int number_of_zero_pending = infileLength%16;
    aes_block* aes_block_array;

    BYTE key[16 * (14 + 1)];
    int keyLen = 0;
    int blockLen = 16;

    ifstream key_fp;
    key_fp.open(argv[2]);
    while(key_fp.peek()!=EOF) {
        key_fp>>key[keyLen];
        if(key_fp.eof())
            break;
        keyLen++;
    }

    cout<<keyLen<<endl;
    switch (keyLen) {
        case 16:break;
        case 24:break;
        case 32:break;
        default:printf("ERROR : keyLen should be 128, 192, 256bits\n"); return 0;
    }

    int expandKeyLen = AES_ExpandKey(key, keyLen);

    if(number_of_zero_pending != 0)
        aes_block_array = new aes_block [ block_number + 1];
    else
        aes_block_array = new aes_block[ block_number ];
    char temp[16];
    
    FILE* en_fp;
    FILE* de_fp;
    en_fp = fopen(argv[3], "wb");
    de_fp = fopen(argv[4], "wb");
    
    for(int i=0; i<block_number; i++){
        ifs.read(temp, 16);
        for(int j=0; j<16; j++){
            aes_block_array[i].block[j] = (unsigned char)temp[j];
        }
    }
    
    if(number_of_zero_pending != 0) {
        ifs.read(temp, number_of_zero_pending);
        for(int j=0; j<16; j++){
            aes_block_array[block_number].block[j] = (unsigned char)temp[j];
        }
        for(int j=1; j<=16-number_of_zero_pending; j++)
            aes_block_array[block_number].block[16-j] = '\0';
        block_number++;
    }

    // Encrypt
    AES_Encrypt(aes_block_array, key, expandKeyLen, block_number);

    for(int i=0; i<block_number-1; i++){
        f1printBytes(aes_block_array[i].block, blockLen, en_fp);
    }
    if(number_of_zero_pending == 0)
        f1printBytes(aes_block_array[block_number-1].block, blockLen, en_fp);
    else 
        f1printBytes(aes_block_array[block_number-1].block, blockLen, en_fp);

    // Decrypt
    AES_Decrypt(aes_block_array, key, expandKeyLen, block_number);

    for(int i=0; i<block_number-1; i++){
        f2printBytes(aes_block_array[i].block, blockLen, de_fp);
    }
    if(number_of_zero_pending == 0)
        f2printBytes(aes_block_array[block_number-1].block, blockLen, de_fp);
    else 
        f3printBytes(aes_block_array[block_number-1].block, blockLen, de_fp);

    AES_Done();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cerr << "Execution time: " << duration.count() << " seconds" << std::flush << std::endl;

    fclose(en_fp);
    fclose(de_fp);
    delete[] aes_block_array;

    return 0;
}