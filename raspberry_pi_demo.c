#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "ilitek_common.h"
#include "ilitek_protocol.h"

// ----------------------------------------- PORT

int fd;

void
ilitek_interface_init ( void )
{
    //  Initialize I2C bus.

    if ( ( fd = open ( "/dev/i2c-1", O_RDWR ) ) < 0 )
    {

    }

    if ( ioctl ( fd, I2C_SLAVE, 0x41 ) < 0 )
    {

    }

    //  Initialize RST.

    //  Initialize INT.

    //  (Optional) Initialize serial port for printout.
}

void
ilitek_delay ( uint32_t msec )
{
    int ret;
    struct timespec start_time;
    struct timespec current_time;
    uint32_t start_msec;
    uint32_t current_msec;

    ret = clock_gettime( CLOCK_REALTIME, &start_time );
    if ( ret != 0 )
    {
        printf( "Error in clock_gettime !\r\n" );
        return;
    }

    start_msec = ( start_time.tv_sec * 1000 ) + ( start_time.tv_nsec / 1000 );

    //  Block here until msec expire.

    for ( ;; )
    {
        ret = clock_gettime( CLOCK_REALTIME, &current_time );
        if ( ret != 0 )
        {
            printf( "Error in clock_gettime !\r\n" );
            return;
        }

        current_msec = ( current_time.tv_sec * 1000 ) + ( current_time.tv_nsec / 1000 );

        if ( ( start_msec + msec ) < current_msec )
        {
            break;
        }
    }
}

void
ilitek_sleep ( uint32_t msec )
{
    ilitek_delay( msec );
}

int
ilitek_i2c_read( uint8_t * data, int rdlen )
{
    if ( rdlen != read( fd, data, rdlen ) )
    {
        return -1;
    }

    return 0;
}

int
ilitek_i2c_rw( uint8_t * cmd, int wrlen, int del, uint8_t * data, int rdlen )
{
    if ( wrlen != write( fd, cmd, wrlen ) )
    {
        return -1;
    }

    if ( del > 0 )
    {
        ilitek_delay( del );
    }

    if ( rdlen != read( fd, data, rdlen ) )
    {
        return -1;
    }

    return 0;
}

void ilitek_gpio_reset_set( uint8_t value )
{
    ( void )value;

}

uint8_t ilitek_gpio_int_get( void )
{
    return 0;
}

void ilitek_print ( const char * fmt, ... )
{
    char str[1024];
    va_list arg;

    va_start( arg, fmt );
    vsprintf( str, fmt, arg );
    va_end( arg );

    printf( str );
}

// ----------------------------------------- PROGRAM

int
main( int argc, char ** argv )
{
    ilitek_interface_init( );
    ilitek_reset( 1000 );

    api_protocol_init_func( );


    for ( ; ; )
    {
        ilitek_read_data_and_report_3XX( );

#if 0
        int i;
        int x_coord;
        int y_coord;

        for (i = 0; i < ILITEK_SUPPORT_MAX_POINT; ++i)
        {
            if (ilitek_data->touch_flag[i] == 1)
            {
                x_coord = ilitek_data->tp[i].x;
                y_coord = ilitek_data->tp[i].y;

                Serial.print( x_coord );
                Serial.print( y_coord );
            }
        }
#endif

    }

    close( fd );
}
