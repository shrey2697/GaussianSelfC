/*THIS CODE CREATES A SMOOTH IMAGE OUT OF A NOISY IMAGE AND SAVE THAT IMAGE SEPARATELY*/

#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <math.h> //for sqrt function

//THE BELOW CODE IS FOR KERNEL DEFINITION
void createFilter(double gKernel[][5])
{
    // set standard deviation to 1.0
    double sigma = 4.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;



    int x,y,i,j;

    for (x = -2; x <= 2; x++)
    {
        for(y = -2; y <= 2; y++)
        {
            r = sqrt(x*x + y*y);
            gKernel[x + 2][y + 2] = (exp(-(r*r)/s))/(M_PI * s);  //Applying the Gaussian Formula to create the matrix
            sum += gKernel[x + 2][y + 2];
        }
    }

    // normalize the Kernel
    for(i = 0; i < 5; ++i)
        for(j = 0; j < 5; ++j)
            gKernel[i][j] /= sum;

}

//KERNEL DEFINITION ENDS HERE

int main( int argc, char** argv )
{
    //KERNEL CREATION

    double gKernel[5][5];
    createFilter(gKernel);
    //KERNEL CREATION ENDS
    int i,j;
   IplImage* img = cvLoadImage("lenagaussian.JPG", CV_LOAD_IMAGE_GRAYSCALE); //read the image data in the file "MyPic.JPG" and store it in 'img'

   IplImage* img1 = cvSaveImage("lenagaussiansmooth1.jpg",img,CV_LOAD_IMAGE_GRAYSCALE);
   img1 = cvLoadImage("lenagaussiansmooth1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
     if (!img1) //check whether the image is loaded or not
     {
          printf("Image cannot be loaded");

          return -1;
     }
    cvNamedWindow("Before",CV_WINDOW_AUTOSIZE);
     cvShowImage("Before",img);  //Display the original image that has to be blurred
     cvWaitKey(0);  //Wait for image for infinite time

  for(i=2; i<(img1->height)-1; i++)   //Go through each row element
     {
         for( j=2; j<(img1->width)-1; j++)   //Go through each column element
         {

            //Convolving Gaussian Matrix with the pixel and with its 8-connected pixels
             CV_IMAGE_ELEM(img1,uchar,i,j) = (CV_IMAGE_ELEM(img1,uchar,i,j)*gKernel[2][2])+ (CV_IMAGE_ELEM(img1,uchar,i+1,j)*gKernel[3][2])+
                                    (CV_IMAGE_ELEM(img1,uchar,i+2,j)*gKernel[4][2])+(CV_IMAGE_ELEM(img1,uchar,i-1,j)*gKernel[1][2])+
                                    (CV_IMAGE_ELEM(img1,uchar,i-2,j)*gKernel[0][2]) + (CV_IMAGE_ELEM(img1,uchar,i,j+1)*gKernel[2][3])+
                                    (CV_IMAGE_ELEM(img1,uchar,i,j+2)*gKernel[2][4]) + (CV_IMAGE_ELEM(img1,uchar,i,j-1)*gKernel[2][1]) +
                                    (CV_IMAGE_ELEM(img1,uchar,i,j-2)*gKernel[2][0]) + (CV_IMAGE_ELEM(img1,uchar,i+1,j+1)*gKernel[3][3])+
                                    (CV_IMAGE_ELEM(img1,uchar,i+2,j+2)*gKernel[4][4])+(CV_IMAGE_ELEM(img1,uchar,i+1,j-1)*gKernel[3][1])+
                                    (CV_IMAGE_ELEM(img1,uchar,i+2,j-2)*gKernel[4][0])+ (CV_IMAGE_ELEM(img1,uchar,i+2,j-1)*gKernel[4][1]) +
                                    (CV_IMAGE_ELEM(img1,uchar,i+1,j-2)*gKernel[3][0])+(CV_IMAGE_ELEM(img1,uchar,i+1,j+2)*gKernel[4][3])+
                                    (CV_IMAGE_ELEM(img1,uchar,i+2,j+1)*gKernel[3][4]) + (CV_IMAGE_ELEM(img1,uchar,i-1,j-1)*gKernel[1][1])+
                                    (CV_IMAGE_ELEM(img1,uchar,i-2,j-2)*gKernel[0][0]) + (CV_IMAGE_ELEM(img1,uchar,i+1,j-1)*gKernel[1][3]) +
                                    (CV_IMAGE_ELEM(img1,uchar,i+2,j-2)*gKernel[0][4]) + (CV_IMAGE_ELEM(img1,uchar,i-2,j-1)*gKernel[1][0])+
                                    (CV_IMAGE_ELEM(img1,uchar,i-1,j-2)*gKernel[0][1])+(CV_IMAGE_ELEM(img1,uchar,i+1,j-2)*gKernel[0][3]) +
                                    (CV_IMAGE_ELEM(img1,uchar,i+2,j-1)*gKernel[0][4]);

         }
     }
     IplImage* img2 = cvSaveImage("lenagaussiansmooth1.jpg",img1,CV_LOAD_IMAGE_GRAYSCALE);
   img2 = cvLoadImage("lenagaussiansmooth1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
     //Display the Image after blurring
 cvNamedWindow("After Smoothing",CV_WINDOW_AUTOSIZE);
     cvShowImage("After Smoothing",img1);
     cvWaitKey(0); //Wait for a key to be pressed for infinite time
     cvReleaseImage(&img1);
}

