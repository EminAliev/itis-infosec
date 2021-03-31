#include "magma.h"
#define _CRT_SECURE_NO_WARNINGS

MAGMA::MAGMA(char key_in[33]) {
    for (int i = 0; i < 33; i++) {
        secretKey[i] = key_in[i];
    }
};


void MAGMA::encode() {

    FILE* input_data;
    FILE* output_data;
    int size;
    unsigned int subBlockBuf;

    for (int i = 0; i < 8; i++) {
        key[i] = (secretKey[4 * i] << 24) + (secretKey[1 + 4 * i] << 16) + (secretKey[2 + 4 * i] << 8) + secretKey[3 + 4 * i]; 
    }

    input_data = fopen(SOURCE, "r");

    fseek(input_data, 0, SEEK_END);
    size = ftell(input_data);
    fseek(input_data, 0, SEEK_SET);

    output_data = fopen(CRYPT, "r+");

    do {
        unsigned int subBlockA = 0; 
        unsigned int subBlockB = 0; 

        if (size >= 4)
        {
            fread(&subBlockA, 4, 1, input_data);
            size -= 4;
        }
        else
        {
            fread(&subBlockA, size, 1, input_data);
            for (int i = 0; i < (4 - size); i++)
            {
                subBlockA += (32 << (24 - (i * 8)));
                size = 0;
            }
        }

        if (size >= 4)
        {
            fread(&subBlockB, 4, 1, input_data);
            size -= 4;
        }
        else
        {
            fread(&subBlockB, size, 1, input_data);
            for (int i = 0; i < (4 - size); i++)
            {
                subBlockB += (32 << (24 - (i * 8)));
                size = 0;
            }
        }

        for (int i = 0; i < 32; i++)
        {
            subBlockBuf = 0;

            if (i < 24) {
                subBlockBuf = (subBlockA + key[i % 8]) % 0x100000000;
            }
            else {
                subBlockBuf = (subBlockA + key[7 - (i % 8)]) % 0x100000000;
            }

            unsigned int smallBlock[8] =
            {
                (subBlockBuf & 0xF0000000) >> 28,
                (subBlockBuf & 0xF000000) >> 24,
                (subBlockBuf & 0xF00000) >> 20,
                (subBlockBuf & 0xF0000) >> 16,
                (subBlockBuf & 0xF000) >> 12,
                (subBlockBuf & 0xF00) >> 8,
                (subBlockBuf & 0xF0) >> 4,
                (subBlockBuf & 0xF)
            };

            for (int j = 0; j < 8; j++)
            {
                smallBlock[j] = sBox[j][smallBlock[j]];
            }

            subBlockBuf = (smallBlock[0] << 28) +
                (smallBlock[1] << 24) +
                (smallBlock[2] << 20) +
                (smallBlock[3] << 16) +
                (smallBlock[4] << 12) +
                (smallBlock[5] << 8) +
                (smallBlock[6] << 4) +
                smallBlock[7];

            subBlockBuf = (subBlockBuf << 11);
            subBlockBuf ^= subBlockB;

            if (i != 31)
            {
                subBlockB = subBlockA;
                subBlockA = subBlockBuf;
            }
            else
            {
                subBlockB = subBlockBuf;
            }
        }

        fwrite(&subBlockA, 4, 1, output_data);
        fwrite(&subBlockB, 4, 1, output_data);
    } while (size != 0);

    fclose(input_data);
    fclose(output_data);

}


void MAGMA::decode() {

    FILE* input_data;
    FILE* output_data;
    int size;
    unsigned int subBlockBuf;

    for (int i = 0; i < 8; i++) {
        key[i] = (secretKey[4 * i] << 24) + (secretKey[1 + 4 * i] << 16) + (secretKey[2 + 4 * i] << 8) + secretKey[3 + 4 * i];  // razbivaem kluck na 8 chastei
    }

    input_data = fopen(CRYPT, "r");

    fseek(input_data, 0, SEEK_END);
    size = ftell(input_data);
    fseek(input_data, 0, SEEK_SET);

    output_data = fopen(DECRYPT, "w");

    do {
        unsigned int subBlockA = 0;
        unsigned int subBlockB = 0;

        if (size >= 4)
        {
            fread(&subBlockA, 4, 1, input_data);
            size -= 4;
        }
        else
        {
            fread(&subBlockA, size, 1, input_data);
            for (int i = 0; i < (4 - size); i++)
            {
                subBlockA += (32 << (24 - (i * 8)));
                size = 0;
            }
        }

        if (size >= 4)
        {
            fread(&subBlockB, 4, 1, input_data);
            size -= 4;
        }
        else
        {
            fread(&subBlockB, size, 1, input_data);
            for (int i = 0; i < (4 - size); i++)
            {
                subBlockB += (32 << (24 - (i * 8)));
                size = 0;
            }
        }

        for (int i = 0; i < 32; i++)
        {
            subBlockBuf = 0;

            if (i < 8) {
                subBlockBuf = (subBlockA + key[i % 8]) % 0x100000000;
            }
            else {
                subBlockBuf = (subBlockA + key[7 - (i % 8)]) % 0x100000000;
            }


            unsigned int smallBlock[8] =
            {
                (subBlockBuf & 0xF0000000) >> 28,
                (subBlockBuf & 0xF000000) >> 24,
                (subBlockBuf & 0xF00000) >> 20,
                (subBlockBuf & 0xF0000) >> 16,
                (subBlockBuf & 0xF000) >> 12,
                (subBlockBuf & 0xF00) >> 8,
                (subBlockBuf & 0xF0) >> 4,
                (subBlockBuf & 0xF)
            };

            for (int j = 0; j < 8; j++)
            {
                smallBlock[j] = sBox[j][smallBlock[j]];
            }

            subBlockBuf = (smallBlock[0] << 28) +
                (smallBlock[1] << 24) +
                (smallBlock[2] << 20) +
                (smallBlock[3] << 16) +
                (smallBlock[4] << 12) +
                (smallBlock[5] << 8) +
                (smallBlock[6] << 4) +
                smallBlock[7];

            subBlockBuf = (subBlockBuf << 11);
            subBlockBuf ^= subBlockB;

            if (i != 31)
            {
                subBlockB = subBlockA;
                subBlockA = subBlockBuf;
            }
            else
            {
                subBlockB = subBlockBuf;
            }
        }

        fwrite(&subBlockA, 4, 1, output_data);
        fwrite(&subBlockB, 4, 1, output_data);
    } while (size != 0);

    fclose(input_data);
    fclose(output_data);
}