#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

int cac(char &tmpc) {
        // *   ?   [   #   ~   =   %
        // |  &  ;  <  >  (  )  $ ` \ " '  <space>  <tab>  <newline>
        if (tmpc == ' ' || tmpc == '(' || tmpc == ')' ||
//              tmpc == '{' || tmpc == '}' ||
                tmpc == '&' || tmpc == '\\' ||
                tmpc == ';' || tmpc == '|' || tmpc == '<' || tmpc == '>' ||
                tmpc == '$' || tmpc == '`' || tmpc == '\"' || tmpc == '\'' ||
                tmpc == '*' || tmpc == '?' || tmpc == '[' || tmpc == ']' ||
                tmpc == '#' || tmpc == '~' || tmpc == '=' || tmpc == '%'
        ) return 1;
        else return 0;
}

int main(void) {
        std::ifstream inc("kkk");
        std::ofstream ouc("mmm");
        char tmpc[1000];
        char tmpd[2000];
        int tmpi, tmpj;
        while (inc.getline(tmpc, 1000)) {
                tmpi = tmpj = 0;
                for (tmpi = 0; tmpi < strlen(tmpc); tmpi++) {
                        if (tmpc[tmpi] == ' ') tmpd[tmpj++] = '.';
                        else if (cac(tmpc[tmpi]) && tmpc[tmpi] != ' ') {
                                tmpd[tmpj++] = '\\';
                                tmpd[tmpj++] = tmpc[tmpi];
                        }
                        else tmpd[tmpj++] = tmpc[tmpi];
                }
                tmpd[tmpj] = '\0';
                ouc << tmpd << '\n';
        }
}
