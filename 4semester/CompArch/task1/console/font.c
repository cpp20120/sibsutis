// #include <stdio.h>

// static const char FONT_CODE_TABLE[18] = "0123456789ABCDEF+-";

// int
// main (int argc, const char *argv[])
// {
//   int error_code = 0;

//   FILE *font_file = NULL;
//   if (argc == 1)
//     font_file = fopen ("font.bin", "w");
//   else
//     font_file = fopen (argv[1], "w");

//   if (font_file == NULL)
//     {
//       printf ("Error! Can't created font file!\n");
//       error_code = 1;
//     }
//   else
//     {
//       for (size_t i = 0; i < sizeof (FONT_CODE_TABLE); ++i)
//         fwrite ((const void *)&FONT_CODE_TABLE[i], sizeof (char), 1,
//                 font_file);
//     }

//   return error_code;
// }

char *
getBigChar (int code)
{
  switch (code)
    {
    case 0:
      return "■■■■■■■■\n\
■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■■■■■■■";
    case 1:
      return "    ■■■ \n\
   ■■■■ \n\
  ■■ ■■ \n\
 ■■  ■■ \n\
     ■■ \n\
     ■■ \n\
     ■■ \n\
     ■■ ";
    case 2:
      return "  ■■■■■■\n\
■■■■■■■■\n\
■■    ■■\n\
     ■■\n\
   ■■   \n\
 ■■     \n\
■■■■■■■■\n\
■■■■■■■■";
    case 3:
      return " ■■■■■■■\n\
■■    ■■\n\
      ■■\n\
   ■■■■■\n\
   ■■■■■\n\
      ■■\n\
■■    ■■\n\
 ■■■■■■■";
    case 4:
      return "■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■■\n\
      ■■\n\
      ■■\n\
      ■■";
    case 5:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■■■■■■■\n\
■■■■■■■■\n\
      ■■\n\
■■■■■■■■\n\
■■■■■■■■";
    case 6:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■■■■■■■\n\
■■■■■■■■\n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■■";
    case 7:
      return "■■■■■■■■\n\
■■■■■■■■\n\
     ■■■\n\
    ■■■ \n\
   ■■■  \n\
  ■■■   \n\
 ■■■    \n\
■■■     ";
    case 8:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■■\n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■■";
    case 9:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■■\n\
      ■■\n\
■■■■■■■■\n\
■■■■■■■■";
    case 10:
      return "   ■■   \n\
  ■■■■  \n\
 ■■  ■■ \n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■■\n\
■■    ■■\n\
■■    ■■";
    case 11:
      return "■■■■■■  \n\
■■■■■■■■\n\
■■    ■■\n\
■■■■■■■ \n\
■■■■■■■ \n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■  ";
    case 12:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■      \n\
■■      \n\
■■      \n\
■■■■■■■■\n\
■■■■■■■■";
    case 13:
      return "■■■■■■  \n\
■■■■■■■■\n\
■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■    ■■\n\
■■■■■■■■\n\
■■■■■■■";
    case 14:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■■■■■■■\n\
■■■■■■■■";
    case 15:
      return "■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■■■■■■■\n\
■■■■■■■■\n\
■■      \n\
■■      \n\
■■      ";
    case 16:
      return " \n\
   ■■   \n\
   ■■   \n\
■■■■■■■■\n\
■■■■■■■■\n\
   ■■   \n\
   ■■   \n\
 ";
    case 17:
      return " \n\
 \n\
 \n\
■■■■■■■■\n\
■■■■■■■■\n\
 \n\
 \n\
 ";
    default:
      break;
    }
  return "";
}