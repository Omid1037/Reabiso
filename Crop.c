#include <stdio.h>
#include <bmpio.h>

unsigned char Pic[2000][2000][3];
unsigned char SecPic[2000][2000][3];
unsigned char Sec2Pic[2000][2000][3];
int NOF(char name);
int CutRight(int height,int width);
int CutLeft(int height,int width,int ny);
int CutUp(int height,int width,int ny,int ny2);
int CutBottom(int height,int width,int ny,int ny2,int nx);
void DrawPic(int nx, int nx2,int ny, int ny2);
void RsizVertical(int height,float RatioH);
int ResizHorizontal(int height,float RatioW,int width);
int main()
{
	int  nx,nx2, ny,ny2,n,ii,jj,kk,zz,number;
	char name;
	char p[100];
	int width, height;
	scanf("%c",&name);
    
    /*
    =======================================
    			START-CROP
	=======================================
    */
    number=0;
    number=NOF(name);
    for(ii=1;ii<=number;ii++){
	sprintf(p,"D:/DataSet/%c/%d.bmp",name,ii);
	readBMP(p, &width, &height, Pic);
	
	ny=CutRight(height, width);
	ny2=CutLeft(height, width,ny);
	nx=CutUp(height,width,ny,ny2);
	nx2=CutBottom(height,width,ny,ny2,nx);
    DrawPic(nx,nx2,ny,ny2);
    sprintf(p,"D:/DataSet/%c/Crop%d.bmp",name,ii);
	saveBMP(SecPic,ny2-ny,nx2-nx,p);
}
	/*
	========================================
				END-CROP
	========================================
	*/


    /*
    =======================================
    			START-RESIZ
	=======================================
    */
	for(ii=1;ii<=number;ii++){
	
	sprintf(p,"D:/DataSet/%c/Crop%d.bmp",name,ii);
	readBMP(p, &width, &height, Pic);
	
	float RatioW,RatioH , h = 0 ;
	int i , j , k , z=0 ;
    RatioW = 500.00 / (float) width ;
    RatioH = 500.00 / (float) height ;

    ResizHorizontal(height,RatioW,width);    
	RsizVertical(height,RatioH);

	sprintf(p,"D:/DataSet/%c/Resiz%d.bmp",name,ii);
    saveBMP(SecPic,500,500,p);

}
	/*
    =======================================
    			END-RESIZ
	=======================================
    */
    
    
    /*
    =======================================
    			START-AVRAGE
	=======================================
    */
       
    for(ii=0;ii<500;ii++){
    	for(jj=0;jj<500;jj++){
    		for(kk=0;kk<500;kk++)
    		SecPic[ii][jj][kk]=0;
		}
	}
     for(zz=1;zz<=number;zz++){
	
	sprintf(p,"D:/DataSet/%c/Resiz%d.bmp",name,zz);
	readBMP(p, &width, &height, Pic);
	for(ii=0;ii<500;ii++){
		for(jj=0;jj<500;jj++){
			for(kk=0;kk<=2;kk++){	
				SecPic[ii][jj][kk]=((double)SecPic[ii][jj][kk]+((double)Pic[ii][jj][kk])/32);
			}	
		}
	}   
}
sprintf(p,"D:/DataSet/%c/AV.bmp",name);
saveBMP(SecPic,500,500,p);

	/*
    =======================================
    			END-AVRAGE
	=======================================
    */
    
    

}
int NOF(char name){
	int Number=0;
	switch(name){
		case 'A':
			Number=32;
			break;
		case 'B':
			Number=41;
			break;
		case 'C':
			Number=32;
			break;
		case 'I':
			Number=15;
			break;
		case 'O':
			Number=25;
			break;
		case 'R':
			Number=17;
			break;
		case 'S':
			Number=20;
			break;
		case 'E':
			Number=32;
			break;
	}
	return Number;
}
int CutRight(int height,int width){
    int count;
    int j,i;
	for(j=0;j<=(width-1) ;j++){
		count=0;
		for(i=0;i<=(height-1);i++){
			if(Pic[i][j][0]!=255 || Pic[i][j][1]!=255 || Pic[i][j][2]!=255){
				count=count+1;
			}
		}
		if(count!=0){
			break;
		}
	}
	return j;
}
int CutLeft(int height,int width,int ny){
    int count;
    int j,i;
	for(j=ny;j<width ;j++){
		count=0;
		for(i=0;i<=(height-1);i++){
			if(Pic[i][j][0]==255 && Pic[i][j][1]==255 && Pic[i][j][2]==255){
				count=count+1;
			}
		}
		if(count==height){
			break;
		}
	}
	return j-1;
}
int CutUp(int height,int width,int ny,int ny2){
    int count;
    int j,i;
	for(i=0;i<=(height-1) ;i++){
		count=0;
		for(j=ny;j<=ny2;j++){
			if(Pic[i][j][0]!=255 || Pic[i][j][1]!=255 || Pic[i][j][2]!=255)
				count=count+1;
			
		}
		if(count!=0){
			break;
		}
		
	}
	return i;
}
int CutBottom(int height,int width,int ny,int ny2,int nx){
    int count;
    int j,i;
	for(i=nx;i<height ;i++){
		count=0;
		for(j=ny;j<ny2;j++){
			if(Pic[i][j][0]==255 && Pic[i][j][1]==255 && Pic[i][j][2]==255)
				count=count+1;
			
		}
		if(count==(ny2-ny)){
			break;
		}
		
	}
	return i-1;
}
void DrawPic(int nx, int nx2,int ny, int ny2){
		int i,j,k;
		for(i=0; i<=nx2-nx ; i++){
		for(j=0 ; j<=ny2-ny; j++){
			for( k=0; k<=2 ; ++k){
				SecPic[i][j][k]=Pic[i+nx][j+ny][k];
			}
		}
	}
	saveBMP(SecPic,ny2-ny,nx2-nx,"CROP.bmp");
}
int ResizHorizontal(int height,float RatioW,int width){
 int i,z,j,k,h,h2;
 for(i=0 ; i<height ; i++) {
    	z=0 ;
    	h = RatioW - (int) RatioW ;
    	float h2 = 0 ; 
    	for(j=0 ; j<width ; j++) {
			if (z!=0 && (j&1)) { 
				SecPic[i][z][0] = h * (float) Pic[i][j-1][0] + (1.0-h) * (float) Pic[i][j][0] ; 
				SecPic[i][z][1] = h * (float) Pic[i][j-1][1] + (1.0-h) * (float) Pic[i][j][1] ; 
				SecPic[i][z][2] = h * (float) Pic[i][j-1][2] + (1.0-h) * (float) Pic[i][j][2] ;	
			} 
			else if (z!=0 && !(j&1)) { 
				SecPic[i][z][0] = h*(float)Pic[i][j][0] + (1.0-h)*(float)Pic[i][j-1][0] ; 
				SecPic[i][z][1] = h*(float)Pic[i][j][1] + (1.0-h)*(float)Pic[i][j-1][1] ; 
				SecPic[i][z][2] = h*(float)Pic[i][j][2] + (1.0-h)*(float)Pic[i][j-1][2] ; 	
			}
			(int)SecPic[i][j][0],SecPic[i][j][1],SecPic[i][j][2];
			printf("%d %d %d /n",SecPic[i][j][0],SecPic[i][j][1],SecPic[i][j][2]);
			h2 += h ; 
			if (h2>=1) {
				z++ ; 
				h2 -= 1 ; 
			} 
			for (k=z ; k < z + (int) RatioW ; k++) {
				SecPic[i][k][0] = Pic[i][j][0] ;
				SecPic[i][k][1] = Pic[i][j][1] ;
				SecPic[i][k][2] = Pic[i][j][2] ;
			}
			z += (int) RatioW ;
		} 
	}
}
void RsizVertical(int height,float RatioH){
	int i,j,z,k;
	float h,h1;
	for (i=0 ; i<height ; i++) {
		for (j=0 ; j<500 ; j++) {
			Sec2Pic[i][j][0] = SecPic[i][j][0] ; 
			Sec2Pic[i][j][1] = SecPic[i][j][1] ; 
			Sec2Pic[i][j][2] = SecPic[i][j][2] ; 
		}
	}
	
	for(i=0 ; i<500 ; i++) {
    	z=0 ;
    	h = RatioH - (int) RatioH ;
    	float h2 = 0 ; 
    	for(j=0 ; j<height ; j++) {
			if (z!=0 && (j&1)) { 
				SecPic[z][i][0] = h * (float) Sec2Pic[j-1][i][0] + (1.0-h) * (float) Sec2Pic[j][i][0] ; 
				SecPic[z][i][1] = h * (float) Sec2Pic[j-1][i][1] + (1.0-h) * (float) Sec2Pic[j][i][1] ; 
				SecPic[z][i][2] = h * (float) Sec2Pic[j-1][i][2] + (1.0-h) * (float) Sec2Pic[j][i][2] ;	
			} 
			else if (z!=0 && !(j&1)) { 
				SecPic[z][i][0] = h*(float)Sec2Pic[j][i][0] + (1.0-h)*(float)Sec2Pic[j-1][i][0] ; 
				SecPic[z][i][1] = h*(float)Sec2Pic[j][i][1] + (1.0-h)*(float)Sec2Pic[j-1][i][1] ; 
				SecPic[z][i][2] = h*(float)Sec2Pic[j][i][2] + (1.0-h)*(float)Sec2Pic[j-1][i][2] ; 	
			}
			h2 += h ; 
			if (h2>=1) {
				z++ ; 
				h2 -= 1 ; 
			}
			for (k=z ; k < z + (int) RatioH ; k++) {
				SecPic[k][i][0] = Sec2Pic[j][i][0] ;
				SecPic[k][i][1] = Sec2Pic[j][i][1] ;
				SecPic[k][i][2] = Sec2Pic[j][i][2] ;
			}
			z += (int) RatioH ;
		} 
	}
}
