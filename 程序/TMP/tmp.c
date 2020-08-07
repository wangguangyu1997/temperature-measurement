#include"tmp.h"
void tmp_to_string(float temp ,unsigned char *tmp)
{
	tmp[0] = (int)(temp/10+'0') ;
	temp = temp - (tmp[0]-'0')*10 ;
	temp = 10*temp ;
	tmp[1] = (int)(temp/10+'0') ;
	temp = temp - (tmp[1]-'0')*10 ;
	temp = 10*temp ;
	tmp[2] = '.' ;
	tmp[3] = (int)(temp/10+'0') ;
	temp = temp - (tmp[3]-'0')*10 ;
	temp = 10*temp ;
	tmp[4] = (int)(temp/10+'0') ;

}

void tmp_to_printf(float temp ,unsigned char *tmp)
{
	temp = temp - (tmp[0]-'0')*10 ;
	temp = 10*temp ;
	tmp[0] = (int)(temp/10+'0') ;
	temp = temp - (tmp[1]-'0')*10 ;
	temp = 10*temp ;
	tmp[1] = '.' ;
	tmp[2] = (int)(temp/10+'0') ;
	temp = temp - (tmp[3]-'0')*10 ;
	temp = 10*temp ;
	tmp[3] = (int)(temp/10+'0') ;
	

}

