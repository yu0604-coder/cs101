#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int n;
    scanf("%d", &n);

    fp = fopen("lotto.txt", "w");


    fprintf(fp, "========= lotto649 =========\n");

    srand(1);

    for (int i = 1; i <= 5; i++) {
        fprintf(fp, "[%d]: ", i);
        if (i <= n) {
            int num[7];
            int j = 0;
            while (j < 7) {
                int r = rand() % 69 + 1;  // 亂數範圍 1~69
                int duplicate = 0;
                for (int k = 0; k < j; k++) {
                    if (num[k] == r) {
                        duplicate = 1;  // 檢查重複
                        break;
                    }
                }
                if (!duplicate) {
                    num[j] = r;
                    j++;
                }
            }
            // 印出 7 個號碼，每個號碼兩位數，後面加空格
            for (int k = 0; k < 7; k++) {
                fprintf(fp, "%02d ", num[k]);
            }
            fprintf(fp, "\n");  // 換行
        } else {
            // 若超出使用者指定組數，用空白樣板補上
            fprintf(fp, "__ __ __ __ __ __ __\n");
        }
    }

    // 結尾
    fprintf(fp, "========= csie@CGU =========\n");

    fclose(fp);
   
    fp =fopen("lotto.txt", "r");
    int lotto[5][7] = {0};
    char line[256];
    int i = 0, j;
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '[') {
            sscanf(line, "[%*d]: %d %d %d %d %d %d %d",
                   &lotto[i][0], &lotto[i][1], &lotto[i][2],
                   &lotto[i][3], &lotto[i][4], &lotto[i][5], &lotto[i][6]);
            i++;
        }
    }
    fclose(fp);

    int in[3];
    printf("請輸入中獎號碼三個: ");
    scanf("%d %d %d", &in[0], &in[1], &in[2]);

    printf("輸入中獎號碼為: %02d %02d %02d\n", in[0], in[1], in[2]);

    printf("以下為中獎彩卷：\n");

    for (int i = 0; i < 5; i++) {
        if (lotto[i][0] == -1) continue;
        int match = 0;
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 3; k++) {
                if (lotto[i][j] == in[k]) match++;
            }
        }
        if (match >= 1) {
            printf("中獎組別 [%d]: ", i + 1);
            for (int j = 0; j < 7; j++){
                printf("%02d ", lotto[i][j]);
                printf("\n");
            }
        }
    }
}
