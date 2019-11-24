#include <asc85.h>
#include <encode85.h>

		////

void	encode_asc85(char * zbuf, int asz, const unsigned char * asrc, int alen)
{
	char c, * zfill ;
	const char * p ;
	unsigned long lval ;
	int istep ;

	if ( ! zbuf || ! asrc || ! asz ) return ;	// bad pointer, or no room for even a null terminator
	asz -- ;  // pre-reserve space for null

	for (zfill= zbuf ; (( alen & ~3 ) && ( asz >= 5 )) ; alen -= 4 )
	{
		lval= * (asrc ++) ;  lval <<= 8 ; lval |= * (asrc ++) ;  lval <<= 8 ;
		lval |= * (asrc ++) ;  lval <<= 8 ; lval |= * (asrc ++) ;

		;
		for ( p= pack_a85( lval); ( c= *( p ++) ) ; -- asz ) { *( zfill ++)= c ; }
	}

	if ( alen && ! ( alen & ~3 ) && ( asz >= ( alen +1 )))	// there's a fragment left, and still space
	{
			// pack 1,2 or 3 bytes
		lval= * (asrc ++) * (1L << 24) ;
		switch ( alen )
		{
			case 3:
				lval |= *( asrc ++) << 16 ;
				lval |= *( asrc ++) << 8 ;
				break ;
			case 2:
				lval |= *( asrc ++) << 16 ;
				break ;
		}

		for ( istep= alen +1, alen= 0, p= pack_a85e( lval) ; ( istep -- && ( *(zfill ++)= *(p ++) )) ; -- asz ) { }
	}

	if ( alen ) {  // src data left over
		if ( ! asz && ( zfill > zbuf ) ) { -- zfill ; }	// back up one to fit the error marker
		*( zfill ++)= '/' ;
	}

	* zfill= '\0' ;
}

int		decode_asc85(unsigned char * zdest, int asz, const char * asrc)
{
	int istep, ival ;
	unsigned long lval ;
	unsigned char * zfill= zdest ;

	if ( ! zdest || ! asz || ! asrc ) return -1 ;

	while ( asz && * asrc )
	{
		if ( '.' == * asrc ) {
			asrc ++ ;
			for ( istep= 4 ; ( istep -- && asz ) ; -- asz ) { *(zfill ++)= 0 ; }
			continue ;
		}

		lval= unpack_a85x( asrc, &ival ) ;
		asrc += ival ;
		if ( ival < 2 ) return -1 ;
		for ( istep= 32, ival -- ; ( istep && ival && asz ) ; -- ival, -- asz ) { istep -= 8 ;  *(zfill ++)= 0xff & ( lval >> istep ) ; }
	}

	return ( zfill - zdest ) ;
}

int		decode_asc85x(unsigned char * zdest, int asz, const char * asrc, int * zuse)
{
	int istep, ival ;
	unsigned long lval ;
	const char * ptr= asrc ;
	unsigned char * zfill= zdest ;

	if ( ! zdest || ! asz || ! asrc ) return -1 ;
	while (( asz > 4 ) && * ptr )
	{
		if ( '.' == * ptr ) {
			ptr ++ ;
			for ( istep= 4 ; ( istep -- && asz ) ; -- asz ) { *(zfill ++)= 0 ; }
			continue ;
		}

		lval= unpack_a85x( ptr, &ival ) ;
		if ( ival < 5 ) break ;
		*(zfill ++)= 0xff & ( lval >> 24 ) ;
		*(zfill ++)= 0xff & ( lval >> 16 ) ;
		*(zfill ++)= 0xff & ( lval >> 8 ) ;
		*(zfill ++)= 0xff & lval ;
		ptr += ival ;
		asz -= 4 ;
	}

	if ( zuse ) { * zuse= ( ptr - asrc ) ; }
	return ( zfill - zdest ) ;
}

