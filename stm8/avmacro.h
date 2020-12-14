#ifndef __AVMACRO_H__
#define __AVMACRO_H__

// Askold Volkov's macros
// impl. by Oleg Terentiev aka Hoksmur

#ifdef __AVR__
// AVR GCC //
#define _setL(port,nbit)          do { PORT##port &= ~(1<<nbit); } while(0)
#define _setH(port,nbit)          do { PORT##port |= (1<<nbit); } while(0)
#define _clrL(port,nbit)          do { PORT##port |= 1<<nbit; } while(0)
#define _clrH(port,nbit)          do { PORT##port &= ~(1<<nbit); } while(0)
#define _bitL(port,nbit)          (!(PIN##port & (1<<nbit)))
#define _bitH(port,nbit)          (PIN##port & (1<<nbit))
#define _inv(port,nbit,val)       do { PORT##port ^= 1<<nbit; } while(0)
#define _dir_out(port,nbit,val)   do { DDR##port |= 1<<nbot; } while(0)
#define _dir_in(port,nbit,val)    do { DDR##port &= ~(1<<nbit); } while(0)
#define _dir(port,nbit,val)       (DDR##port & (1<<nbit))
#define _pull_off(port,nbit,val)  do {PORT##port &= ~(1<<nbit);} while(0)
#define _pull_on(port,nbit,val)   do {PORT##port |= 1<<nbit;} while(0)
#define _set(port,nbit,val)       _set##val(port,nbit)
#define _clr(port,nbit,val)       _clr##val(port,nbit)
#define _bit(port,nbit,val)       _bit##val(port,nbit)

////////////////////////////////////////////////////////////////////////////////////
#define dir_out(x)                _dir_out(x)
#define dir_in(x)                 _dir_in(x)
#define dir(x)                    _dir(x)
#define on(x)                     _set(x)
#define off(x)                    _clr(x)
#define is_active(x)              (!! _bit(x))
#define toggle(x)                 _inv(x)
#define pull_off(x)               _pull_off(x)
#define pull_on(x)                _pull_on(x)


#elif defined (__SDCC_stm8)
  /* === STM8 SDCC === */
/* using:
 * #define PC5 GPIO, 5
 *   pin_mode(PC5, OUT_OPEN_DRAIN);
 *	 pin_out( PC5, HIGH); 
 *  !! Only HIGH and LOW to output!!
 */
#define IN_NOPULL_NOINT   0,0,0
#define IN_PULLUP_NOINT   0,1,0
#define IN_NOPULL_INT     0,0,1
#define IN_PULLUP_INT     0,1,1
#define OUT_OPENDRAIN     1,0,0
#define OUT_PUSHPULL      1,1,0
#define OUT_OPENDRAIN_FAST  1,0,1
#define OUT_PUSHPULL_FAST   1,1,1
#define OUT_OPENDRAIN_TRUE  1,0,1

#define _iowrite_1(port, pin)  do{ port->ODR |=   1<<(pin) ;} while(0)
#define _iowrite_0( port, pin)  do{ port->ODR &= !(1<<(pin)); }while(0) 
#define _ioread(port, pin)  (port->IDR & (1<<(pin)))
#define _pin_out(PORT, PIN, LVL)  _iowrite_##LVL( PORT, PIN)
#define _pin_togl(port, pin)  do{ port->ODR ^= 1<<(pin); }while(0)
//#define _mode(P, M)  _set_mode( p, num, ddr, cr1, cr2)
#define _set_mode( p, num, ddr, cr1, cr2)  _set_dir( p, num, ddr); \
	_set_cr1( p, num, cr1); \
	_set_cr2( p, num, cr2);
#define _set_dir( p, num, ddr)  do{ p->DDR &= ~(1<<(num)); p->DDR |= ddr<<(num); }while(0)
#define _set_cr1( p, num, cr1)  do{ p->CR1 &= ~(1<<(num)); p->CR1 |= cr1<<(num); }while(0)
#define _set_cr2( p, num, cr2)  do{ p->CR2 &= ~(1<<(num)); p->CR2 |= cr2<<(num); }while(0)
/////////////  ---  A  - P  - I  ---//////////////////////////////////////////////////////
#define pin_mode(P, M)  _set_mode(P, M)
#define pin_write(P, LVL) _pin_out(P, LVL)
#define pin_toggle(P)   _pin_togl(P)
#define pin_read(P)     _ioread(P)
  /* === STM8 SDCC end === */

#elif defined (__CSMC__) 
  #if ( __TRGT__ == "STM8" )
  // STM8 Cosmic //
  #endif
#else
	#error unknow platform!

#endif



#endif /* __AVMACRO_H__ */
