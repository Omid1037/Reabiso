#include <stdio.h>
#include <bmpio.h>

unsigned char Pic[2000][2000][3];
unsigned char SecPic[2000][2000][3];
int CutRight(int height,int width);
int CutLeft(int height,int width,int ny);
int CutUp(int height,int width,int ny,int ny2);
int CutBottom(int height,int width,int ny,int ny2,int nx);
void DrawPic(int nx, int nx2,int ny, int ny2);
int main()
{
	int  nx,nx2, ny,ny2;
	char p[100];
	gets(p);
	int width, height;
	readBMP(p, &width, &height, Pic);
    
    /*
    ======================================
    			START-CROP
	======================================
    */
	ny=CutRight(height, width);
	ny2=CutLeft(height, width,ny);
	nx=CutUp(height,width,ny,ny2);
	nx2=CutBottom(height,width,ny,ny2,nx);
    DrawPic(nx,nx2,ny,ny2);
	
	/*
	========================================
				END-CROP
	========================================
	*/

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
	saveBMP(SecPic,ny2-ny,nx2-nx,"OFCP12.bmp");
}
