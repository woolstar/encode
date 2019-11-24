
		//// buffer operators

extern void	encode_asc85(char * zdest, int asz, const unsigned char * asrc, int alen) ;
extern int	decode_asc85(unsigned char * zdest, int asz, const char * asrc) ;
extern int	decode_asc85x(unsigned char * zdest, int asz, const char * asrc, int * zuse) ;

