//==============================================
//  ライフゲーム
//  
//  2015.04.24 moxtsuan
//  2016.04.20 moxtsuan unix移植
//==============================================

//==============================================
//  概要
//==============================================
//  はじめに縦と横のサイズを入力、
//  二次元配列に値(0か1)を格納していく。
//  隣接するセルが3つならば誕生、
//  2つか3つならば生存
//  隣接するセルが4以上の場合は窒息死、
//  1以下の場合孤独死する。
//  詳しくは「ライフゲーム」でググろう。

//==============================================
//  関数説明
//==============================================
//  arr_inputは配列へ格納、
//  arr_copyは配列の複写、
//  next_genは生死判定を行う。
//  next_genの判定はnext_calcを用いる。
//  next_calcは隣接するセルが3なら1、2なら2、
//  それ以外なら0を返す。
//  arr_compは配列の比較を行う。
//  同じなら0、そうでなければ1を返す。
//  

//==============================================
//  include
//==============================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//==============================================
//  define
//==============================================
#define SIZE 101
#define WAIT 500*1000
//==============================================
//  プロトタイプ宣言
//==============================================
void arr_input( int arr[][SIZE], int len, int wid );                      // 配列に数値を格納する
void arr_output( int arr[][SIZE], int len, int wid );                     // 画面に出力する
void arr_copy( int arr1[][SIZE], int arr0[][SIZE], int len, int wid );    // 配列をコピーする
int arr_comp( int arr[][SIZE], int pre[][SIZE], int len, int wid );       // 配列が同じか調べる
void next_gen( int arr[][SIZE], int pre[][SIZE], int len, int wid );      // 次の世代へ移行する
int next_calc( int arr[][SIZE], int l_pos, int w_pos, int len, int wid ); // 生死判定を行う


//==============================================
//  大域変数
//==============================================

//==============================================
//  主処理
//==============================================

int main(void)
{
    int cell[SIZE][SIZE];   // セル
    int pre[SIZE][SIZE];    // 前世代のセル
    int len, wid;           // 縦横
    int gen;                // 世代
    int flag;               // 打ち切りフラグ
    
    scanf("%d %d", &len, &wid);
    
    //---- 初期化
    gen = 0;
    
    arr_input( cell, len, wid );
    
    //---- 第0世代の表示
    printf("gen%d\n", gen);     // 何世代目か表示
    arr_output( cell, len, wid );
    usleep(WAIT);
    system("clear");
    
    while(1) {
        arr_copy( pre, cell, len, wid );
        next_gen( cell, pre, len, wid );
        flag = arr_comp( cell, pre, len, wid );
        
        if ( !flag ) {
            break;
        } else {
            gen++;
            printf("gen%d\n", gen);
            arr_output( cell, len, wid );
        }
        //---- アニメーション用
        usleep(WAIT);     // 500ミリ秒(0.5秒)止める
        system("clear");  // 画面をクリアする
    }
    
    return 0;
}

void arr_input( int arr[][SIZE], int len, int wid )
{
    int i, j;
    
    for ( i=0; i<len; i++ ) {
        for ( j=0; j<wid; j++ ) {
            scanf("%1d", &arr[i][j]);
        }
    }
    
}

void arr_output( int arr[][SIZE], int len, int wid )
{
    int i, j;
    
    for ( i=0; i<wid+2; i++ ) {
        printf("-");
    }
    putchar('\n');
    for ( i=0; i<len; i++ ) {
        putchar('|');
        for ( j=0; j<wid; j++ ) {
            if ( arr[i][j] == 0 ) {
                printf(" ");
            } else {
                printf("■");
            }
        }
        putchar('|');
        putchar('\n');
    }
    
    for ( i=0; i<wid+2; i++ ) {
        printf("-");
    }
    putchar('\n');
}

void arr_copy( int arr1[][SIZE], int arr0[][SIZE], int len, int wid )
{
    int i, j;
    
    for ( i=0; i<len; i++ ) {
        for ( j=0; j<wid; j++ ) {
            arr1[i][j] = arr0[i][j];
        }
    }
    
}

int arr_comp( int arr[][SIZE], int pre[][SIZE], int len, int wid )
{
    int i, j;
    
    for ( i=0; i<len; i++ ) {
        for ( j=0; j<wid; j++ ) {
            if ( arr[i][j] != pre[i][j] ) {
                return 1;
            }
        }
    }
    return 0;
}

void next_gen( int arr[][SIZE], int pre[][SIZE], int len, int wid )
{
    int tmp;
    int i, j;
    
    for ( i=0; i<len; i++ ) {
        for ( j=0; j<wid; j++ ) {
            tmp = next_calc( pre, i, j, len, wid );
            if ( tmp == 2 ) {
                arr[i][j] = pre[i][j] & 1;
            } else {
                arr[i][j] = tmp;
            }
        }
    }
    
}

int next_calc( int arr[][SIZE], int l_pos, int w_pos, int len, int wid )
{
    int sum = 0;
    int i,j;
    
    for ( i=l_pos-1; i<=l_pos+1; i++ ) {
        for ( j=w_pos-1; j<=w_pos+1; j++ ) {
            if ( (i == l_pos) && ( j == w_pos ) ) {
                continue;
            }
            if ( i < 0 || i > len ) {
                continue;
            }
            if ( j < 0 || j > wid ) {
                continue;
            }
            sum += arr[i][j];
            
        }
    }
    
    //---- 生死判定
    if ( sum == 3 ) {
        return 1;
    } else if ( sum == 2 ) {
        return 2;
    } else {
        return 0;
    }
    
}