#include <stdio.h>
#include <string.h>

#define Mod 1000000007

int main() {
    char buff[2002];

    FILE * in = fopen("ursi.in", "rt");
    fscanf(in,"%s",buff+1);
    fclose(in);

    int len = (int)strlen(buff);

    int long long dp[len][len];
    dp[0][0] =1;
    for(int i=1; i<len; i++)
        dp[0][i] = 0;

    int nr = 0;
    char c;
    for (int i = 1; i < len; i++) {
        c = buff[i];

        for (nr = 0; nr < len; nr++) {

            if (c == '^') {

                if (nr - 1 < 0) {
                    dp[i][nr] = dp[i - 1][nr + 1] % Mod;
                } else if (nr + 1 >= len) {
                    dp[i][nr] = (nr * dp[i - 1][nr - 1]) % Mod;
                } else {
                    dp[i][nr] = (nr * dp[i - 1][nr - 1]) % Mod
                                + dp[i - 1][nr + 1] % Mod;
                }

            } else {
                dp[i][nr] = (nr * dp[i - 1][nr]) % Mod;
            }
        }
    }



    FILE * out = fopen("ursi.out", "wt");
    fprintf(out,"%lli",dp[len -1][0]);
    fclose(out);

    return 0;
}
