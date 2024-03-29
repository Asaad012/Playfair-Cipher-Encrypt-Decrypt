#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
static char matrix [5][5];

void ciphertext(char *plaintext, int mode){
    int extendedSize = 2*strlen(plaintext);
    char newPlaintext [extendedSize];

    int positionNewPlaintext = 0;
    for (int i = 0; i < strlen(plaintext); i+=2) {
        char pairs[3];
        pairs[0] = plaintext[i];
        pairs[1] = plaintext[i+1];
        if(!pairs[1]){
            pairs[1] = 'Z';
        }
        if(pairs[0] == pairs[1]){
            newPlaintext[positionNewPlaintext] = pairs[0];
            newPlaintext[positionNewPlaintext+1] = 'X';
            i--;
        } else{
            newPlaintext[positionNewPlaintext] = pairs[0];
            newPlaintext[positionNewPlaintext+1] = pairs[1];
        }
        positionNewPlaintext+=2;
        pairs[0]=0;
        pairs[1] = 0;
    }

    int end = positionNewPlaintext;
    //int length = 0;
    for (positionNewPlaintext = 0; positionNewPlaintext < end-1; positionNewPlaintext+=2) {
        int check = 0;
        //rule 1 column check
        for (int i = 0; i < 5; ++i) {
            check = 0;
            for (int j = 0; j < 5; ++j) {
                if (matrix[i][j] == newPlaintext[positionNewPlaintext]){
                    for (int k = 0; k < 5; ++k) {
                        if(matrix[k][j] == newPlaintext[positionNewPlaintext + 1]){
                            if(mode == 0){
                                if(i == 4){
                                    i = -1;
                                }
                                if(k == 4){
                                    k = -1;
                                }
                                newPlaintext[positionNewPlaintext] = matrix[i + 1][j];
                                newPlaintext[positionNewPlaintext+1] = matrix[k + 1][j];
                            } else{
                                if(i == 0){
                                    i = 5;
                                }
                                if(k == 0){
                                    k = 5;
                                }
                                newPlaintext[positionNewPlaintext] = matrix[i - 1][j];
                                newPlaintext[positionNewPlaintext+1] = matrix[k - 1][j];
                            }

                            check =1;
                            break;
                        }
                    }
                }
                if(check){
                    break;
                }
            }
            if(check){
                break;
            }
        }
        if(!check){
            // rule 2 row check
            for (int i = 0; i < 5; ++i) {
                check = 0;
                for (int j = 0; j < 5; ++j) {
                    if (matrix[i][j] == newPlaintext[positionNewPlaintext]){
                        for (int k = 0; k < 5; ++k) {
                            if(matrix[i][k] == newPlaintext[positionNewPlaintext + 1]){
                                if(mode == 0){
                                    if(j == 4){
                                        j = -1;
                                    }
                                    if(k == 4){
                                        k = -1;
                                    }
                                    newPlaintext[positionNewPlaintext] = matrix[i][j+1];
                                    newPlaintext[positionNewPlaintext+1] = matrix[i][k+1];
                                } else{
                                    if(j == 0){
                                        j = 5;
                                    }
                                    if(k == 0){
                                        k = 5;
                                    }
                                    newPlaintext[positionNewPlaintext] = matrix[i][j-1];
                                    newPlaintext[positionNewPlaintext+1] = matrix[i][k-1];
                                }

                                check =1;
                                break;
                            }
                        }
                    }
                    if(check){
                        break;
                    }
                }
                if(check){
                    break;
                }
            }
        }
        if(!check){
            //rule 3
            int row1 = 0;
            int column1 =0;
            int row2 = 0;
            int column2 =0;
            for (int i = 0; i < 5; ++i) {
                check = 0;
                for (int j = 0; j < 5; ++j) {
                    if (matrix[i][j] == newPlaintext[positionNewPlaintext]){
                        row1 = i;
                        column1 = j;

                        check =1;
                        break;
                    }
                }
                if(check){
                    check = 0;
                    break;
                }
            }
            for (int i = 0; i < 5; ++i) {
                check = 0;
                for (int j = 0; j < 5; ++j) {
                    if (matrix[i][j] == newPlaintext[positionNewPlaintext+1]){
                        row2 = i;
                        column2 = j;
                        check =1;
                        break;
                    }
                }
                if(check){
                    check = 0;
                    break;
                }
            }
            newPlaintext[positionNewPlaintext] =  matrix[row1][column2];
            newPlaintext[positionNewPlaintext+1] =  matrix[row2][column1];
//     LP PK NP MV WQ ZU EZ KZ LV CU PQ AL FW WF PO
        }

    }

    if(mode == 0){
        printf("This is your ciphertext:\n");
    } else{
        printf("This is your plaintext:\n");
    }
    for (int i = 0; i < positionNewPlaintext; i+=2) {
        printf("%c%c ", newPlaintext[i], newPlaintext[i+1]);
    }
    printf("\n");


}
void keymatrix(char *secretKey, char *alpha){
    char tmpMatrix[25];
    char clearedSecretkey[25];
    int counter = 0;
    for (int i = 0; i < strlen(secretKey); ++i) {
        for (int j = i+1; j < strlen(secretKey); ++j) {
            if(secretKey[i] == secretKey[j]){
                secretKey[j] = ' ';
            }
        }
        if(secretKey[i] != ' '){
            clearedSecretkey[counter] = secretKey[i];
            counter ++;
        }
    }

    secretKey = clearedSecretkey;
    counter =0;
    for (int i = 0; i < 25 && i < strlen(secretKey); ++i) {
        tmpMatrix[i] = secretKey[i];
        counter++;
    }
    int alphaCounter=0;
    int alphaMatchSecretkey = 0;
    for (int i = counter; i < 25; ++i) {
        for (int j = 0; j < strlen(secretKey); ++j) {
            if(alpha[alphaCounter] == secretKey[j]){
                alphaMatchSecretkey = 1;
                break;
            }
        }
        if(alphaMatchSecretkey){
            alphaCounter++;
            alphaMatchSecretkey =0;
            i-=1;
        } else{
            tmpMatrix[i] = alpha[alphaCounter];
            alphaCounter++;
        }
    }
    counter = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = tmpMatrix[counter];
            counter++;
        }
    }
}
int main() {
    char secretKey[100];
    printf("Please enter your secret key: ");
    scanf("%s", secretKey);
    char alpha[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M',
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    //call method 1 to print and generate key matrix
    keymatrix(secretKey, alpha);

    //handling the plain text plaintext breaked when user plaintext "EOS"
    char plaintext[1000];
    int index = 0;
    printf("If you want to encrypt message enter 0 if decrypt enter 1: ");
    int mode = 0;
    scanf("%d", &mode);
    if(mode == 0){
        printf("Enter plaintext type EOS to end");
    } else{
        printf("Enter ciphertext type EOS to end\n");
    }
    while (1) {
        char c = getchar();
        if (c == EOF) {
            break;
        }
        if (c == ' ' || c == '\n' || ispunct(c)) {
            continue;
        }
        plaintext[index++] = c;

        // Check if the last 3 characters form 'EOS'
        if (index >= 3 && strncmp(&plaintext[index - 3], "EOS", 3) == 0) {
            // Remove 'EOS' from the plaintext
            index -= 3;
            break;
        }
        if (index >= 999) {
            break;
        }
    }
    printf("\nYour key matrix table is:\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    // Ensure the plaintext is properly null-terminated
    plaintext[index] = '\0';
    //mode 0 is encrypt, mode 1 is decrypt
    ciphertext(plaintext, mode);
    return 0;
}


