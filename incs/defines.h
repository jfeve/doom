/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   defines.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:40:55 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 17:30:37 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define WIN_W 1500
# define WIN_H 1000
# define WF_W 200
# define WF_H 150
# define TEXT_SY 5
# define TEXT_S 1
# define UNIT 15
# define HUD_BEGIN 851
# define TEXT_INPUT 1000
# define PIXFOR SDL_PIXELFORMAT_RGBA8888
# define SDL_BUTTON_LEFT 1
# define SDL_BUTTON_MIDDLE 2
# define SDL_BUTTON_RIGHT 3
# define SDL_BUTTON_X1 4
# define SDL_BUTTON_X2 5
# define MAP_PATH "./data/maps/"
# define WHITE 0xFFFFFFFF
# define DARK 0x000000FF
# define WF_COL 0xCCA800FF
# define RED 0xFF0058FF
# define CYAN 0x4863B5FF
# define SKYBLUE 0x73C2D1FF
# define PURPLE 0x8820E8FF
# define BROWN 0x673415FF
# define GREEN 0x00A800FF
# define YELLOW 0xFFFF4DFF
# define _0_ "311113\n211312\n2101212\n2101212\n2121012\n213112\n311113\0"
# define _1_ "514\n211114\n514\n514\n514\n514\n21111112\0"
# define _2_ "31114\n21313\n514\n415\n316\n217\n2111113\0"
# define _3_ "31114\n21313\n613\n4114\n613\n21313\n31114\0"
# define _4_ "217\n217\n217\n21015\n2111113\n415\n415\0"
# define _5_ "2111113\n217\n217\n2111113\n712\n712\n2111113\0"
# define _6_ "311113\n217\n217\n2111113\n21412\n21412\n311113\0"
# define _7_ "21111112\n712\n613\n514\n514\n514\n514\0"
# define _8_ "311113\n21412\n21412\n311113\n21412\n21412\n311113\0"
# define _9_ "311113\n21412\n21412\n3111112\n712\n21412\n311113\0"
# define _CURSOR_ "65\n515\n515\n515\n515\n515\n515\n65\0"
# define _EQUAL_ "82\n82\n0111111110\n82\n82\n0111111110\n82\n82\0"
# define _POINT_ "82\n82\n0000110000\n82\n82\n0000110000\n82\n82\0"
# define _SLASH_ "82\n7100\n0000001000\n5103\n4104\n3105\n2106\n0107\n82\0"
# define _A_ "28\n28\n311113\n21412\n21111112\n21412\n21412\n28\0"
# define _B_ "28\n28\n2111113\n21412\n2111113\n21412\n2111113\n28\0"
# define _C_ "28\n28\n3111112\n217\n217\n217\n3111112\n28\0"
# define _D_ "28\n28\n2111113\n214100\n21412\n21412\n2111113\n28\0"
# define _E_ "28\n28\n21111112\n217\n211114\n217\n21111112\n28\0"
# define _F_ "28\n28\n21111112\n217\n211114\n217\n217\n28\0"
# define _G_ "9\n9\n21111112\n017\n01211110\n01510\n2111112\n7\0"
# define _H_ "28\n28\n21412\n214100\n21111112\n21412\n21412\n28\0"
# define _I_ "3\n3\n410\n3\n410\n410\n410\n3\0"
# define _J_ "28\n28\n712\n7100\n7100\n21412\n311113\n28\0"
# define _K_ "28\n28\n21214\n21015\n2116\n21015\n21214\n28\0"
# define _L_ "28\n28\n217\n217\n217\n217\n2111113\n28\0"
# define _M_ "28\n28\n21412\n2112112\n21011012\n21412\n21412\n28\0"
# define _N_ "28\n28\n211312\n2101212\n2121012\n213112\n21412\n28\0"
# define _O_ "28\n28\n311113\n21412\n21412\n21412\n311113\n28\0"
# define _P_ "28\n28\n2111113\n21412\n2111113\n217\n217\n28\0"
# define _Q_ "28\n28\n311113\n21412\n21412\n2121112\n3111112\n28\0"
# define _R_ "28\n28\n2111113\n21412\n2111113\n21412\n21510\n28\0"
# define _S_ "28\n28\n3111112\n217\n311113\n712\n2111113\n28\0"
# define _T_ "8\n8\n21111102\n414\n414\n414\n414\n8\0"
# define _U_ "28\n28\n21412\n21412\n21412\n21412\n211111100\n28\0"
# define _V_ "28\n28\n21412\n21412\n21412\n2112112\n4114\n28\0"
# define _W_ "28\n28\n21412\n21412\n21412\n21011012\n31213\n28\0"
# define _X_ "28\n28\n21412\n21412\n311113\n21412\n214100\n28\0"
# define _Y_ "28\n28\n21312\n21312\n2111112\n414\n414\n28\0"
# define _Z_ "28\n28\n21111112\n712\n613\n514\n316\n21111112\n28\0"
# define _COMMA_ "28\n28\n28\n28\n415\n415\n316\n28\n28\0"
# define TUTO "l click = vertex / h = highlight\0"
# define HL_SET_TUTO "left/right = change sector / enter = select\0"
# define HL_TUTO "o = obj / e = enem / zx = cancel obj/enem / t = input mode\0"
# define FLOOR "floor = \0"
# define CEIL "ceil = \0"
# define VEC "vec \0"
# define OBJ "obj \0"
# define ENEM "enem \0"
# define DUCK 3
# define EYE 6
# define KNEE 2.5
# define HEADMARGE 1
# define HFOV (0.73f * WIN_H)
# define VFOV (0.2f * WIN_H)
# define DIFICULTY "Diff \0"
# define PLAYER_OR "player look \0"
# define GRAVITY "gravity \0"
#endif
