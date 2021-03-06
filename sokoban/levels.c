/**************************************************************************
 * Program for STM32F429 Disbovery using gcc and libopencm3
 * Sokoban puzzle game
 * by Marcos Augusto Stemmer
 * Levels
****************************************************************************/
#include <stdlib.h>
/********************************************
 * Space: Empty floor
 * W Wall
 * M Man
 * X Place to store the box
 * B Box
 * m Man with X
 * b Box with X
 * ******************************************/
const char *solutions[]=
{
/* 1*/	"kikkmmmmjmkjjmjjiimmkkiikkiiijjjkmkmkmmjjmjjik",
/* 2*/	"mmjjmmkkikkiiiijjijmkmjikkkmmmmjjiiimmmkkiiiij"
	"jjkmmmjjmkmkiiiimmmkkiiiijjijmkmmmmmmkimjiiiiiikkmmmmjmjiiiimmmkkiiiijj",
/* 3*/	"mkkkiiikkiijjmikkmmjjmmjmkkkijmjiiikkiijjmmmmjmkjjjikkmkiiimmkkmjjjkiii"
	"kkiijjmmmmjmkiiiiijjmmkjiikkmmmmjjjmk",
/* 4*/	"kiiiimmmkkmkiimjjjiiikkkkmjkiiiijjjjmmmkkikmjjjiiikkkkmmkmjjmmmjjjmjjik"
	"kkkmkiiikiiiijjjjmmmmmiiiiikkkkmmmmjmmjjjmjjikkkkmkii",
/* 5*/	"iiijmkmmmmmjmjjijiiikiikkikmmmmmiiiijjjmmmjmmkmkkikiiijimkmmmjmjjijiiik"
	"iikkikmmmmiiijjjmmmjmmkkkjjjiikmjmkkjiiijjjmkkikmmjmkiiijjjiikmmjmkkikm"
	"miiijmjjiikmjmkikmmm",
/* 6*/	"ijmjiimmkkkkijjjmjijjiiijiikmmjmkmmkkkkkiiikiijjmjjjkkkikkmmjmmmjjjjjii"
	"jiiikmmikkkkikmmmmiiijjjjjjmmmkmkkkmkkkijjkiijikijjjjkkkkmmmmmjjjijjiji"
	"ikmjiiikmmikkkkkmmmmjjj",
/* 7*/	"mjmmmjmmkiiiijiiikkmmjmjikkiijjjjmjmmkkkikmmmjmmkiiiijjjjiikikkkkmmjmmm"
	"jjimkkiiikiijjjjmjmmkkkjjjiikikkkkmmjmmmjmmjiiimkkiiikiijjjjmjmmkkkjmmk"
	"kiijjjjjjmmkkimjjiikkkkkjjjiikiijmmmmjjmmkkimjjiikkkkmmmmkkii",
/* 8*/	"kikikikkmjmjijikkmmjmjimmjmjjkkikiijmikkiijmkmmjjikmkiijikmmmjjjmjmmkik"
	"imjjikikjmmkikiijmkmjijmkmjijmkmjiikkkiikiijmkmmjjikmkii",
/* 9*/	"mmmmmjmmmkkikkmkkiiiiijjiijikkkjjmmmkijikkjmmkmmmmmjjijiikiiikiijjmkkjm"
	"mmmjmmjmjjiiikiikkjjmmjmmmkkikiikiiiijikkjmmmjjjjiiikmmjmkkkjjmmjmmmkki"
	"kiikiiikiijjmkmmjjjmmjmmkiiiikkkmmjmmjmjijiikiijiikmjmkkkjjmmjmmkkkiiki"
	"iiijikmmmmmjmmjjiiiijiikmjmkkkjjmmmmkkiikiiiimkmkmmmmjjjjmjiiiiijiikmjm"
	"kkkjjmmmmkkiikiii",
/*10*/	"mmmjjiiiijmkmmmjjiikikmiiiijmmkmmjjmmkkkkiiiikiijmjjmmmmiiiikkkmmjmmmjj"
	"jkiijjjmmmkikkiiiijmkmmmjjjiikkjjmmkkkiiimmmkkiiikiijjjijmmmkmmmjjjiikk"
	"ikmjiiikmikkkmmjikijjkmmmmmjjmmkkiiiiimmmjjjjjiikkkmijjjmmkkkiijiikmmii"
	"jiikmmikkkmmjikijjkmmmmmmmjjiijjjiikkkmmiijiikmmmiiijiikmmmmjjmjmk iikmm"
	"miiijiikmmmmjjmjmk",
/*11*/	"kkmjmmmmjjikkiijjjjmmmmmmkkkkiimmjjjjiiiiiikkkkmmjmkjjmkiikiijjjjmmmmmmk"
	"kkkiijiikiiiijmkmjjjijmmmmmiiiikkkkmmjmmkiiiijiikkmjijmkmjjjijmmmmiiikkk"
	"kmmmmkkijmjiiiijiikkmjijmkmjjjijmmmiikkkkmmmkkijmjiiijiikkmjijmkmjjjijmmi"
	"kkkkmmkkijmjiijiikkmjijmkmjjjijm",
/*12*/	"kikkkkmkiiiiikijjjjjijmmikkkkkmmmmmjjjjjmjjiiikkkijjmjmmmkkikkkkkmmmjjik"
	"mkiiiiiiikijjjjjijmmikkkkkmmmmmjjjjmjjjiiikikkjjmjmmmkkkikkmijjmkkkmkiii"
	"iiikijjjjjijmmikkkkkmmmmmjjjjjmjjiiikkkijmjjmmmkkmmkijikkkkmkiiiiiikijjj"
	"jjijmmikkkkkmmmmmmmmjjiijikkmkiiiiikijjjjjijmkkkkkmmmmmjjjjjmjjiiikkkkkij",
/*13*/	"kijiikkmjijmikkkkkmmjjimkkiijjjkmmmmkmmjiiiikkiijjjmjmmmmkjiiiikikkkmmjj"
	"mjkmkmmjijjiikkmkmjiiikkiijjmmmmiiijjjikkkmmmjjimkkiiijjjmkmmjimkkkikkii"
	"jjjjkkmmmmkmmjiiiiimkkiijjjkmmmjjmmkjiikkmkmmjiiiiimkkiijj",
/*14*/	"iijjjjjkmmmjjijiimmkmmjiiimkmmmmmmimkkkkkkiijjjjjkkkkkmmjjjjjjiiiimmkkkk"
	"kmikmmjjjjjkkkkiijjjjjiijiikmmmmiiikkmkkkmmmkmjjjjkkkiiiijjjiiiikkkkmmjj"
	"jkkmmjjjiiimkkkkiijjjjmmmjjmmmkkkkkiiimjjjiiiikkkkmmjjjkkmmjjjiii",
/*15*/	"ikkkjiiiiijjijiikikkmmmmmmmmjmmkkijiiiiikkikiijjijmmmmmmmmiiiiikimmjjjik"
	"jjiikkjjmmkkikkmjmjjijiikikkkkmkmmjmjjmmmmjjmmkkiiiiiimmmmjjmkmkiiiimmmm"
	"kkkijjmjiiimmkkijmji",
/*16*/	"kkkmmmmmmmjjjjijjmmmkkkkkkikijjjijiimmjjjiiiikkmmkmmkmkkiiiiiiijjjjjmikk"
	"kkkmmmmmmmjjijiikiikjmmjjiikkmmjmmjjjiiiikkjjmmmmmmmkkiimmkkkkiijjijjkkm"
	"jijmkiiijiijiikkkkkmmmmmmiiiiiijjjjjmmjmmmmmmmkkkkkkikijjjijiikiikjmmjji"
	"ijiikkkkkmmmmmmiiiijjmmjmmkmkkiiiiijjmmjjiikkkjjjjiikkkkkmmmmmmiiiijjmmj"
	"mmjmkkjiiikiijmmmmjmkiiiiijjjmmmmkkjjiiiikkkmmmmjjjmmmkki",
/*17*/	"kkkmkkkiiikijjjjijmmikkkkmmmmjjjijjjiiiiijiikmkkikmmmkmjijmkkkkmmmmjjjij"
	"jjiiiiijikkkikmmijjjmmmmmmkkkmkkkiiiijjijmkkkmmmmjjjijjmkkkkjjjjijiiiiii"
	"kkkmmmkkkmmmkmmjiiiikijjjj",
/*18*/	"mjjjjiikkikmjmikkmmjjiiiiiikkkmjjijmmmmiijjikkkijijmkmmjjikmkikikkmjjjmj"
	"jikikkjjmmkikijmkkkijmjjmmmkkmmjjiiiiimmmmmkmmjikikiijm",
/*19*/	"ikkiiiijjijjmikkmjkkkmmjimkmmjimjjikmkkiiijjmmiikkmmmjjijmmmmiiiikikmkmj"
	"jijmmmiiikiiiijjjmkkikmmmmkmjijmmiikiiijjjmmkijikkikmmmmkmjijmikiiijjjmm"
	"jmmkiijikmkijikkikmmmkmjiikkijjmmmkkijjiiijjmkikmmmmkmj",
/*20*/	"jjjjmkjijjmmmkkkkiikijjkmmmjjjjiikkkjjjmmkkkkiijjjiiiiiijjmkikmmmmmjmmmk"
	"kkkiikiiijjiijjkkmmkkiijjkkmmmmmjjikmkiiimmjmmmjjjjiikkkjjjmmkkkkiikijmj"
	"jjiiiiiijjmkikmmmmmjmkkkjjjmmkkkkiikiiijjiijjijjmkikmmmmiiikkkkmmm",
/*21*/	"iijjmmjjijmjjjiiimmkkiiikiijmmmmmkmjijjiijiikkjjmmkmmkkiiikiijmmmmiiijjjm"
	"mkmmkkmkkijjkkmkkijjmjjiiiiijjjmmkmmmmmjmmkiiimmkkkkkiiijjjiiiiijjmmmiiik"
	"kkmjmmmmkkijmkkkijjkkiijmmkmjjjkkkiikkmmjjjjkmmkijiiikkkmjjjkkmjj",
/*22*/	"ijkkikiijjjmmiikkkmmjmmkmmmjjjjiiijiikmmmmjmkikmmikkkiiijjijkmkkmmmjjjjii"
	"ijiikmmmmmiiiikkkikiijjjmmiikkkmmjmjjijmmmmiiiikiikkmjijmmjmmmmkmkkkiiijj"
	"ijijjmmkmmjmkkjiiijiikmmmmkmjiiiikkkikijjijmmikkmmmkmmmjjkkiiijjijijmmmm",
/*23*/	"jmmjjmmkijikmkiiijikikmmjmkjmmjjmmmkiiijikmkiikijjkmmmkmmjkiijjjmmmkiiiji"
	"kmkiiikijjkmmmmjmmmmkijiiikkmmjmjiiijikmkiiiikijjkmmmmmkmmkmjjmjiiiijikmk"
	"iikijmmmkkmkkijjjjkmmjjiijikmkiiikiijjmkikmmjmmmkmmmkiikijjjkmmjjiijikmki"
	"iikijmmmmkkkkmmjjjjmjiiijikmkiiiikij",
/*24*/
	"kkkkkiijjmikkmmjjjjiijjmmmmkkkkiikkmjjijjjiijjmmkkkkkmkiiiiiikijjijjjmmkki"
	"kijjijmmjmkmkkiikkmmmmmmjjjjiijmjmkkkkkmkiiiiiikijjijjjmmmkkiikijjijmmikkk"
	"mkmmmmmmjjjjjjmmkijikkkkkmkiiiiiikijjijjjjmmmkkkiikijjijmkkkmkmmmmmmjjjjjm"
	"mkijikkkkmkiiiiiikijjijjjjmmmkkkiikijjjijmkkkkmkmmmmmmjjjjmmkijikkkmkiiiii"
	"ikijjijjjjjmmkmkkkiikijjjkkkmkmmmmmmjjjmmkijikkmkiiiiiikijjijjijjjmmmkmkkk"
	"iikijmkkmmmmjjmikkmmmjjjikkmkiiiiiikijjijmkkmmmmmmjjjjikmkkkiijjmjmkkmkiii"
	"iiikijjijijjmkijjjmkkjjmmkijik",
/*25*/	"kkiijjkkmmjjijiiiiiiimjjiikkmmmmmmmmkmkkiiiijijkmkmmmmjjijiiiiiikkiikkmmmm"
	"jkiiiijjmmjjjjiikkkkmmjjimkkiijjjkmmmmmmmmkmkkiijjmjiiiiiiimkkiijjmmmmmmmk"
	"kkiijjkkmmjjjiiiiikkiijjmikkmmjjjkmmmkkkijjmjiiikkiijjmikkmmjjmmmmmkiikijm"
	"jiiimmkkkkiiiijjkkmmjj",
	
};

const char *levels[]={
	/** Level 1 **/
	"         \n"
	"   WWWWW \n"
	" WWW   W \n"
	" WXMB  W \n"
	" WWW BXW \n"
	" WXWWB W \n"
	" W W X WW\n"
	" WB bBBXW\n"
	" W   X  W\n"
	" WWWWWWWW\n",
	/** Level 2 **/
	" \n"
	"  WWWW  \n"
	" WW  WWW\n"
	" WXX B W\n"
	" WXXMW W\n"
	" WWWBW W\n"
	" W   W W\n"
	" W B   W\n"
	" W  B WW\n"
	" WWW  W \n"
	"   WWWW \n",
	/** Level 3 **/
	" \n"
	"  WWWWWWW\n"
	"  W     W\n"
	"  W W W W\n"
	"  W     W\n"
	" WWWW WWW\n"
	" WM BBB W\n"
	" W  XXX W\n"
	" WWWWWWWW\n",
	/** Level 4 **/
	"  WWWWWWW\n"
	"  W     W\n"
	"  W WWW WW\n"
	"  W W B  W\n"
	"  W  XX  W\n"
	"  W WXX  W\n"
	"WWW WW WWW\n"
	"W BBB  W\n"
	"W M W  W\n"
	"WWWWWWWW\n",

	/** Level 5 */
	"WWWW WWWW\n"
	"W  WWW  W\n"
	"W  W BB W\n"
	"W BB W  W\n"
	"W    W MW\n"
	"W B  WW WW\n"
	"WWW B WX W\n"
	"  WXXbXXXW\n"
	"  WW   WWW\n"
	"   WWWWW\n",
	/** Level 6 **/
	"     WWW  \n"
	"WWWW W WWW\n"
	"W  WWW   W\n"
	"W BB  B  W\n"
	"W  WWW   W\n"
	"W XXXW  WW\n"
	"W XWXWWBWW\n"
	"WW X B B W\n"
	" WWW  M  W\n"
	"   WWWWWWW\n",
	/** Level 7 **/
	"  WWWW    \n"
	"  W  WWWWW\n"
	"  W  B   W\n"
	"  W  WXWMW\n"
	"WWWBWWXX W\n"
	"W   B XXWW\n"
	"W W WBWbW\n"
	"W   W   W\n"
	"WWWWWB  W\n"
	"    W   W\n"
	"    WWWWW\n",
	/** Level 8 **/
	"    WWWWWW\n"
	"    W XXXW\n"
	"   WW  B W\n"
	"  WW  B WW\n"
	" WWM B WW\n"
	"WW  B WW\n"
	"WX B WW\n"
	"WX  WW\n"
	"WWWWW\n",
	/** Level 9 **/
	"WWWWWWWWWW\n"
	"W  W XXXXW\n"
	"W BW XXXXW\n"
	"W MWWBBWWW\n"
	"W     B W\n"
	"WWBWWBW W\n"
	"W  W  W W\n"
	"W  W WW W\n"
	"W B B   W\n"
	"W   W   W\n"
	"WWWWWWWWW\n",
	/** Level 10 **/
	"  WWWWWWW\n"
	"  W  W  W\n"
	"  WB BB W\n"
	"  W  W  W\n"
	"WWWB WM W\n"
	"W    W WW\n"
	"W  WXW W\n"
	"W  XXX W\n"
	"W  WXWBW\n"
	"WWWW   W\n"
	"   WWWWW \n",
	/** Level 11 **/
	"   WWWWW\n"
	"WWWWM  W\n"
	"W  W B W\n"
	"W    BWWW\n"
	"WXWWW B W\n"
	"WXW B   W\n"
	"WXW     W\n"
	"WXW B   W\n"
	"WXWWW WWW\n"
	"W     W\n"
	"WWWWWWW\n",
	/** Level 12 **/
	"  WWWW\n"
	"  W  WWWWW\n"
	"  W\n"
	"WWWXWWWW\n"
	"WXXXX  W W\n"
	"W      W W\n"
	"W WWWWWW W\n"
	"W W B    W\n"
	"W M BBBB W\n"
	"WWW  W   W\n"
	"  W  W   W\n"
	"  WWWWWWWW\n",
	/** Level 13 **/
	"\n WWWWWWWW\n"
	" WXXX   W\n"
	" WX XBW W\n"
	" W BW   W\n"
	" WM B WWW\n"
	" WW W  W\n"
	"  W BB W\n"
	"  WWW  W\n"
	"    WWWW\n",
	/** Level 14 */
	"WWWW\n"
	"WX WWWWWWW\n"
	"WXXXX  B W\n"
	"WBWW WWW W\n"
	"W  W   BMW\n"
	"W  B WWBWW\n"
	"W  W     W\n"
	"WW WWWWBWW\n"
	" W     B W\n"
	" WXWWWWB W\n"
	" WXX     W\n"
	" WWWWWWWWW\n",
	/** Level 15 */
	"WW     WW\n"
	"W  bXb  W\n"
	"W WBBBW W\n"
	"W  bXb  W\n"
	"WW     WW\n"
	" WWWXWWW \n"
	"   WXW\n"
	" WWWXWWW\n"
	" W   B WW\n"
	" W  B   W\n"
	" WM     W\n"
	" WWWWWWWW\n",
	/** Level 16 */
	" WWWWWWWW\n"
	" W  M   W\n"
	"WWBWWWWBW\n"
	"W B   B W\n"
	"W W   W W\n"
	"W W   W W\n"
	"W WWBWW W\n"
	"W     W WW\n"
	"W XXXXbXXW\n"
	"W WBWWW  W\n"
	"W       WW\n"
	"WWWWWWWWW\n",
	/** Level 17 **/
	"WWWWWWW\n"
	"  W   W\n"
	"   B  W\n"
	" BWW WWWWW\n"
	"W WX  W  W\n"
	"W WX   B W\n"
	"W WX WW  W\n"
	"W WXWWW WW\n"
	"WM   WW  W\n"
	"WW B     W\n"
	" WWWWWW  W\n"
	"      WWWW\n",
	/** Level 18 **/
	"  WWWW\n"
	"  W  WWWW\n"
	" WWbXX  W\n"
	" W B  B W\n"
	" W   WWWW\n"
	" WWW  WW\n"
	" W B   W\n"
	" W WB MW\n"
	" W XXX W\n"
	" WWWB WW\n"
	"   W  W\n"
	"   WWWW\n",
	/** Level 19 **/
	" WWWWWW\n"
	" W    WWW\n"
	"WW B  B W\n"
	"W   W BXW\n"
	"W B WB  W\n"
	"W  WXBB W\n"
	"W  WX   W\n"
	"W  WXMWWW\n"
	"WWWWXWW\n"
	"   WXW\n"
	"   WXW\n"
	"   WWW\n",
	/** Level 20 **/
	"WWWWW\n"
	"W   WWWWW\n"
	"W B B B W\n"
	"WWW W W W\n"
	"  W W   W\n"
	" WW WWW WW\n"
	" W XXXXXMW\n"
	" W B B   W\n"
	" W WWW WWW\n"
	" W     W\n"
	" WWWWWWW\n",
	/** Level 21 **/
	"WWW  W\n"
	"  B  W\n"
	"  W  WWWW\n"
	"  W WW  WWW\n"
	"WBWBW B\n"
	"WXXXXXB B\n"
	"WXXXXXBBBM\n"
	"W WWXWB WW\n"
	"  WWWW  W\n"
	" B     WW\n"
	"  WWWWWW\n"
	"WWW\n",
	/** Level 22 **/
	"   WWWWWW\n"
	"   W    W\n"
	" WWWBBB W\n"
	" W B W  W\n"
	" W  B  WW\n"
	" W  WM  W\n"
	" WW WWW W\n"
	" W   WW W\n"
	" WXXX   W\n"
	" WWX WWWW\n"
	"  WWXW\n"
	"  WWWW\n",
	/** Level 23 (Anderj Cerjak) */
	"WWWWWW\n"
	"WXX  W\n"
	"WXX  W\n"
	"WXX MWW\n"
	"WWWBXXW\n"
	"W   WWWWW\n"
	"W B     W\n"
	"W  W B  W\n"
	"W BBB B W\n"
	"W  B  WWW\n"
	"WW  WWW\n"
	" WWWW\n",
	/** Level 24 **/
	"W     WW\n"
	"W  XXX WWW\n"
	"W  XWX   W\n"
	"W  XXXW  W\n"
	"WW    W WW\n"
	"WWWWWWW W\n"
	"W   W   W\n"
	"W B BBW W\n"
	"W M     W\n"
	"W BBBBB W\n"
	"W     WWW\n"
	"WWWWWWW\n",
	/** Level 25 **/
	"WWWWWWWWW\n"
	"WXX X   W\n"
	"W WXW W W\n"
	"WXX X B W\n"
	"WWW WWW W\n"
	"  W B B W\n"
	"  W B  WW\n"
	"  W BW W\n"
	"  W B  W\n"
	"  W BW W\n"
	"  WWM  W\n"
	"   WWWWW\n",
	NULL
};
