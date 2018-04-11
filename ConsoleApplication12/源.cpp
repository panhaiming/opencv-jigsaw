#include <iostream>
#include <opencv2/opencv.hpp>  
using namespace cv;
using namespace std;
Mat Sourceimage, jigsawimage,Sp;
int rows, cols;
int Roirows, Roicols;
int  a_num[3][3], b[3][3],a_src[3][3];
int m, n, my, nx,p;
int xx = 0;
vector<Mat>arraryimage;
vector<Mat>dstimage;
static int vectornumber = 0;
void  Randimage(vector<Mat>& vectorMat)
{
	int i1, i2, j1, j2;
	
	for (int i = 0; i<vectorMat.size(); i++)
	{

		int a = rand() % 8;
		swap(vectorMat[i], vectorMat[a]);
		
		
	}
	int a1 = rand() % 8;
	Sp = Mat::zeros(vectorMat[a1].rows, vectorMat[a1].cols, vectorMat[a1].type());
	addWeighted(vectorMat[a1], 0, Sp, 1, 0, vectorMat[a1]);
	p = a1;
	cout << p;

}

void OnMouseAction(int event, int x, int y, int flags, void *ustc)
{
	if (event &EVENT_LBUTTONDOWN)
	{


		Mat RoiSpilte, RoiSource;
		int rows = (y / Roirows)*Roirows;
		int clos = (x / Roicols)*Roicols;
		int py = y / Roirows;
		int px = x / Roicols;
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (i == py&&j == px)
				{
					if ((i < 2 && b[i + 1][j] == 0) || (i > 0 && b[i - 1][j] == 0) || (j<2 && b[i][j + 1] == 0) || (j>0 && b[i][j - 1] == 0))
					{
						Mat SpilterRoi = jigsawimage(Rect(j*Roicols, i*Roirows, Roicols - 1, Roirows - 1));

						for (int i1 = 0; i1 < 3; i1++)
							for (int j1 = 0; j1 < 3; j1++)
							{
								if (b[i1][j1] == 0)
								{
									addWeighted(SpilterRoi, 0, arraryimage[a_num[i1][j1]], 1, 0, SpilterRoi);
									n = i1;
									m = j1;
								}
							}

						Mat SpilterRoi1 = jigsawimage(Rect(m*Roicols, n*Roirows, Roicols - 1, Roirows - 1));

						addWeighted(SpilterRoi1, 0, arraryimage[a_num[i][j]], 1, 0, SpilterRoi1);
						imshow("Jigsaw image", jigsawimage);
						waitKey(150);
						nx = i;
						my = j;
						b[n][m] = 1;
						b[nx][my] = 0;
						int mm = a_num[n][m];
						a_num[n][m] = a_num[nx][my];
						a_num[nx][my] = mm;						
					}
				}
			}
		}


	}

}

void win()
{


	
}


int main(int argc, char*argv[])
{
	Sourceimage = imread("23_out.bmp");
	imshow("Source image", Sourceimage);
	rows = 3;
	cols = 3;
	Roirows = Sourceimage.rows / rows;
	Roicols = Sourceimage.cols / cols;

	jigsawimage = Mat::zeros(Sourceimage.rows, Sourceimage.cols, Sourceimage.type());
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Mat SourceRoi = Sourceimage(Rect(j*Roicols, i*Roirows, Roicols - 1, Roirows - 1));
			arraryimage.push_back(SourceRoi);

		}
	}
	int i0 = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a_src[i][j] = i0++;
		}
	}
	


	Randimage(arraryimage);
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{



			Mat SpilterRoi = jigsawimage(Rect(j*Roicols, i*Roirows, Roicols - 1, Roirows - 1));
			addWeighted(SpilterRoi, 0, arraryimage[vectornumber], 1, 0, SpilterRoi);
			vectornumber++;
			imshow("Jigsaw image", jigsawimage);
			waitKey(150);


		}
	}
	i0 = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a_num[i][j] = i0++;
			b[i][j] = 1;
			if (a_num[i][j]==p)
				b[i][j] = 0;

		}
	}

	setMouseCallback("Jigsaw image", OnMouseAction);


	waitKey();

}

