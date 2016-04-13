#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Ope {AND, OR, NAND, NOR, XOR};

int LogOpe(enum Ope ope, int bit1, int bit2)
{
  switch ( ope ) {
    case AND:
    return bit1 & bit2;
    case OR:
    return bit1 | bit2;
    case NAND:
    return ! ( bit1 & bit2 );
    case NOR:
    return ! ( bit1 | bit2 );
    case XOR:
    return bit1 ^ bit2;
    default:
    break;
  }
}

char* getOpe(enum Ope ope)
{
  switch ( ope ) {
    case AND:
    return "AND";
    case OR:
    return "OR";
    case NAND:
    return "NAND";
    case NOR:
    return "NOR";
    case XOR:
    return "XOR";
    default:
    return "ERROR";
  }
}

char* getPlayer(int n)
{
  if ( n == 0 ) {
    return "Player1";
  } else {
    return "Player2";
  }
}

int getRand(int min, int max)
{
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int getDab(enum Ope o1, enum Ope o2)
{
  return ! ( o1 ^ o2 );
}

int getNum(int min, int max)
{
  int n;
  char t[9];

  fgets(t, 8, stdin);
  n = atoi(t);
  while ( n < min || max < n ) {
    printf("%d 以上 %d 以下の値を入力してください\n", min, max);
    fgets(t, 8, stdin);
    n = atoi(t);
  }
  return n;
}

int main(void)
{
  enum Ope ope[2];
  int score1, score2;
  int ope_n;
  int res;
  int bit1, bit2;
  int max_count;  // 試合回数
  int count;
  int game_end = 0;
  int difficult = 2;  // 需要不明につきHARD固定
  int dab;  // ダブり判定

  srand((unsigned)time(NULL));

  while ( ! game_end ) {
    /*
    printf("難易度を入力(EASYはXORが出ません)\n");
    printf("1:EASY 2:HARD : ");
    difficult = getNum(1, 2);
    */
    printf("試合回数を入力(1以上10以下) : ");
    max_count = getNum(1, 10);
    count = 0;
    score1 = score2 = 0;
    while ( count < max_count*2 ) {
      if ( difficult == 1 ) {
        do {
          ope[0] = getRand(0, 3);
          ope[1] = getRand(0, 3);
        } while ( getDab(ope[0], ope[1]) );
      } else {
        do {
          ope[0] = getRand(0, 4);
          ope[1] = getRand(0, 4);
        } while ( getDab(ope[0], ope[1]) );
      }
      printf("TURN %d\n", count+1);
      printf("%sのターンです.\n", getPlayer(count%2));
      printf("Player1の得点 : %d\n", score1);
      printf("Player2の得点 : %d\n", score2);
      printf("演算は %s か %s.\n", getOpe(ope[0]), getOpe(ope[1]));
      printf("Player1の入力(0か1) : ");
      bit1 = getNum(0, 1);
      printf("Player2の入力(0か1) : ");
      bit2 = getNum(0, 1);

      ope_n = getRand(0, 1);
      printf("使用した演算は %s.\n", getOpe(ope[ope_n]));
      res = LogOpe(ope[ope_n], bit1, bit2);
      printf("%d %s %d は %d.\n", bit1, getOpe(ope[ope_n]), bit2, res);
      printf("%s は %d 点獲得しました.\n\n", getPlayer(count%2), res);
      if ( count % 2 == 0 ) {
        score1 += res;
      } else {
        score2 += res;
      }
      count++;
    }
    printf("Player1の得点 : %d\n", score1);
    printf("Player2の得点 : %d\n", score2);
    if ( score1 > score2 ) {
      printf("Player1の勝ちです.\n");
    } else if( score1 == score2 ) {
      printf("引き分けです.\n");
    } else {
      printf("Player2の勝ちです.\n");
    }
    printf("もう1回やりますか?(0:Yes 1:No) : ");
    game_end = getNum(0, 1);
  }
  return 0;
}
