#ifndef BTN_H__
#define BTN_H__

#define BTN_1 0
#define BTN_2 1

#define BTN_BIT_1 (1 << 0)
#define BTN_BIT_2 (1 << 26)

extern void btn_init();
extern void btn_push(int btn_id);
extern void btn_release(int btn_id);

#endif
