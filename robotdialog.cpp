#include <QtGui>

#include "robotdialog.h"

#include<iostream>
using namespace std;

#include "Graphm.h"
#include "ShortestPath.h"

#define max_corners 29
#define radis 20
#define SLOPEEPS 0.0001
#define STEPRATE 20

RobotDialog::RobotDialog(QWidget *parent)
	:QDialog(parent)

{
	setupUi(this);
	stepNumber=0;
	cornerNumber=0;
	connect(MapButton, SIGNAL(clicked()), this, SLOT(mapOpen()));
	connect(NextButton, SIGNAL(clicked()), this, SLOT(nextStep()));
	NextButton->setVisible(false);
}

void RobotDialog::mapOpen()
{
	imageName=QFileDialog::getOpenFileName(this , "Select Map", ".", "Images (*.png *.bmp *.jpg)");
	if(!imageName.isEmpty()){
//        QPixmap p(imageName);
		p.load(imageName);
		lastpixmap=p;
        mapView->setPixmap(p);
        mapView->setGeometry(0, 0, p.width()/4, p.height()/4);
		stepNumber=0;
		cornerNumber=0;
		cornerpoint.clear();
		NextButton->setVisible(true);
    }
}

void RobotDialog::nextStep()
{
	switch(stepNumber)
	{
		case 0: 	getCorner(imageName); drawCorner(); sortCorner(cornerpoint); stepNumber++; break;
		case 1:		p=lastpixmap; houghMap(imageName); fitMap(); stepNumber++;break;
		case 2:		getRoute(); stepNumber++; break;
		case 3:		p=lastpixmap; FindShortest(2,26);stepNumber++;break;
		case 4:		p=lastpixmap; FindShortest(6,26);stepNumber++;break;
		case 5:		p=lastpixmap; FindShortest(17,26);stepNumber++;break;
		default:	break;
	}
}

void RobotDialog::getCorner(const QString & image)
{
	if(!imageName.isEmpty())
	{
		char* filename=new char[image.length()+1];
		strcpy(filename, (const char*)image.toLocal8Bit());
		
		int cornerCount=max_corners;
		CvPoint2D32f corners[ cornerCount ];
		IplImage *srcImage = 0, *grayImage = 0, *corners1 = 0, *corners2 = 0;
		int i;
		CvScalar color = CV_RGB(255,0,0);
		srcImage = cvLoadImage(filename, 1);
		grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);
		cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
		corners1= cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_32F, 1);
		corners2= cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_32F, 1);
		cvGoodFeaturesToTrack (grayImage, corners1,
												corners2, corners,
		  										&cornerCount, 0.08,
												15, 0, 3, 0, 0.4 );
		cornerNumber=cornerCount;
//		cornerpoint=new PointPos[cornerNumber];
		printf("num corners found: %d\n", cornerCount);
		
		CvMemStorage* storage = cvCreateMemStorage(0);
		cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
		cvSmooth(grayImage, grayImage, CV_GAUSSIAN, 9, 9);
		CvSeq* circles = cvHoughCircles(grayImage, storage, CV_HOUGH_GRADIENT, 1,
									   1, 1, 30, 0, 50);
		CvSeq* circlesP = cvHoughCircles( grayImage, storage, CV_HOUGH_GRADIENT, 2, grayImage->height/4, 200, 100, 30 );
		
		if(cornerCount>0)
		{
			for (i=0; i<cornerCount; i++)
			{
//				painter.drawEllipse((int)corners[i].x-10,(int)corners[i].y-10, radis, radis);
//				cornerpoint[i].x=(int)corners[i].x;
//				cornerpoint[i].y=(int)corners[i].y;
				PointPos ps;
				ps.x=(int)corners[i].x;
				ps.y=(int)corners[i].y;
				cornerpoint.push_back(ps);
			}
		}

		for( int i = 0; i <circles-> total; i++)
		{
			float* tmp=(float *)cvGetSeqElem(circles, i);
			PointPos p;
			p.x=(int)cvRound(tmp[0]);p.y=(int)cvRound(tmp[1]);
			if (p.x>1100)
			{
				ptEnd.push_back(p);
				printf("End Point: %d, %d\n", p.x, p.y);
			}
			else
			{
				ptStart.push_back(p);
				printf("Start Point: %d, %d\n", p.x, p.y);
			}
			cornerpoint.push_back(p);
		}
		tmpImage=p.toImage();
		for( int i=0; i<circlesP->total; i++)
		{
			float* tmp=(float *)cvGetSeqElem(circlesP, i);
			int x=(int)cvRound(tmp[0]), y=(int)cvRound(tmp[1]);
			QRgb rgb=tmpImage.pixel(x, y);
			centerP.push_back(rgb);
		}
		cout << "Center P number: " << centerP.size()<< endl;

		cvReleaseImage(&srcImage);
		cvReleaseImage(&grayImage);
		cvReleaseImage(&corners1);
		cvReleaseImage(&corners2);
	}
}

void RobotDialog::drawCorner()
{
	QPainter painter(&p);
	QBrush redbrush(Qt::red);
	painter.setBrush(redbrush);
	if(cornerNumber>0)
	{
		for (int i=0; i<cornerNumber; i++)
		{	painter.drawEllipse(cornerpoint[i].x-10,cornerpoint[i].y-10, radis, radis);

			cout << i <<" "<<cornerpoint[i].x <<" "<< cornerpoint[i].y <<endl;
		}
		mapView->setPixmap(p);
	}
}

void RobotDialog::sortCorner(vector<PointPos>& corner)
{
	for( unsigned int i=0; i<corner.size()-1; i++)
	{
		for(unsigned int j=1; j<corner.size()-i; j++)	
			if (corner[j].x < corner[j-1].x || (corner[j].x == corner[j-1].x && corner[j].y < corner[j-1].y))
			{
				PointPos p=corner[j-1];
				corner[j-1]=corner[j];
				corner[j]=p;
			}
	}
	corner[0].id=0;
	for( unsigned int i=1; i<corner.size(); i++)
	{
		corner[i].id=i;
		if(ISEQUAL(corner[i], corner[i-1]))
		{
			corner.erase(corner.begin()+i);
			i--;
		}
	}
}

void RobotDialog::drawRoute()
{
	QPainter painter(&p);
	QPen redpen(Qt::red);
	painter.setPen(redpen);
	for(int i=0; i<= cornerNumber+4; i++)
	{
		QPoint corneri(cornerpoint[i].x,cornerpoint[i].y);
		for(int j=0; j<= cornerNumber+4; j++)
		{
			QPoint cornerj(cornerpoint[j].x, cornerpoint[j].y);
			painter.drawLine(corneri,cornerj);
		}
	}
	mapView->setPixmap(p);
}

void RobotDialog::houghMap(const QString & image)
{
	if(!imageName.isEmpty())
	{
		char* filename=new char[image.length()+1];
		strcpy(filename, (const char*)image.toLocal8Bit());
		
		IplImage* src=cvLoadImage(filename, 0);
		IplImage* dst=cvCreateImage(cvGetSize(src),8,1);
		IplImage* color_dst = cvCreateImage( cvGetSize(src),8, 3 );
		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* lines = 0;
		cvCanny( src, dst, 50, 200, 3 );
		cvCvtColor( dst, color_dst, CV_GRAY2BGR );
		lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/360, 64, 20, 20 );
		printf("Lines found: %d\n", lines->total);
		int sm;
		for(int  i = 0; i < lines->total; i++ )
		{
			CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
			LinePos lp;
			if((line[0].x<line[1].x) || (line[0].x==line[1].x && line[0].y<line[1].y))
				sm=0;
			else
				sm=1;
			lp.start.x=line[sm].x;
			lp.start.y=line[sm].y;
			lp.end.x=line[1-sm].x;
			lp.end.y=line[1-sm].y;
			houghLine.push_back(lp);
		}
		cvReleaseImage(&src);
		cvReleaseImage(&dst);
		cvReleaseImage(&color_dst);
	}
}

void RobotDialog::sortLine(vector<LinePos>& line)
{
	for( unsigned int i=0; i<line.size()-1; i++)
	{
		for(unsigned int j=1; j<line.size()-i; j++)	
			if (line[j].start.x < line[j-1].start.x || (line[j].start.x == line[j-1].start.x && line[j].start.y < line[j-1].start.y) 
						 || (line[j].start.x == line[j-1].start.x && line[j].start.y == line[j-1].start.y && line[j].end.x < line[j-1].end.x)
						 || (line[j].start.x == line[j-1].start.x && line[j].start.y == line[j-1].start.y && line[j].end.x == line[j-1].end.x && line[j].end.y < line[j-1].end.y))
			{
				LinePos p=line[j-1];
				line[j-1]=line[j];
				line[j]=p;
			}
	}
	for( unsigned int j=1; j<line.size(); j++)
	{
		if	(line[j].start.x == line[j-1].start.x && line[j].start.y == line[j-1].start.y && line[j].end.x == line[j-1].end.x && line[j].end.y == line[j-1].end.y)
		{	line.erase(line.begin()+j);	j--;	}
	}
	for(unsigned int i=0; i<line.size(); i++)
		line[i].length=distance(line[i].start, line[i].end);
}

void RobotDialog::fitMap()
{
	int flag=0;
	printf("Corner Number: %d\n", cornerpoint.size());
	int eraseflag[houghLine.size()];
	cout <<houghLine.size() <<endl;
	for(unsigned int i=0; i<cornerpoint.size(); i++)
	{	
		for(unsigned int j=0; j<houghLine.size(); j++)
		{
			if(flag){flag=0;	}
			if(fabs(houghLine[j].start.x-cornerpoint[i].x)<15 && fabs(houghLine[j].start.y-cornerpoint[i].y)<15)
			{
// The Lines are Exactly detected
				for(unsigned int k=i+1; k<cornerpoint.size(); k++)
					if(fabs(houghLine[j].end.x-cornerpoint[k].x)<15 && fabs(houghLine[j].end.y-cornerpoint[k].y)<15)
					{
						LinePos lp;
						lp.start=cornerpoint[i];
						lp.end=cornerpoint[k];
						mapLine.push_back(lp);
						eraseflag[j]=1;
						flag=1;
						break;
					}
// Partly detected, and use the help of slope
				if(!flag)
				{
					float slope=(houghLine[j].end.y-houghLine[j].start.y)/(houghLine[j].end.x-houghLine[j].start.x);
					vector<int> idxfit;
					for(unsigned int k=i+1; k<cornerpoint.size(); k++)
					{
						if(cornerpoint[k].x==cornerpoint[i].x) continue;
						float sl=(cornerpoint[k].y-cornerpoint[i].y)/(cornerpoint[k].x-cornerpoint[i].x);
						if(fabs(sl-slope)<SLOPEEPS*slope) idxfit.push_back(k);
					}
					int fixidx=0;
					if(idxfit.size()==0)
						continue;
					else if(idxfit.size()==1)
						fixidx=idxfit[0];
					else
					{
						fixidx=idxfit[0];
						float distmp=distance(cornerpoint[fixidx], cornerpoint[i]);
						for(unsigned int l=1; l<idxfit.size(); l++)
						{
							float tmp=distance(cornerpoint[idxfit[l]], cornerpoint[i]);
							if(distmp>tmp)
								fixidx=idxfit[l];
						}
						LinePos lp;
						lp.start=cornerpoint[i];
						lp.end=cornerpoint[fixidx];
						mapLine.push_back(lp);
						eraseflag[j]=1;
						flag=1;
						break;
					}
				}
			}
		}
	}

	sortLine(mapLine);
// 	for(unsigned int i=0; i<mapLine.size();i++)
// 	{
// 		printf("Line %d, %d -> %d, %d \n", mapLine[i].start.x, mapLine[i].start.y, mapLine[i].end.x, mapLine[i].end.y);
// 	}
 	printf("Map line number: %d\n", mapLine.size());
	QPainter painter(&p);
	QPen redpen(Qt::red);
	redpen.setWidth(5);
	painter.setPen(redpen);
	for(unsigned int i=0;i<mapLine.size();i++)
	{
		QPoint startpt(mapLine[i].start.x,mapLine[i].start.y);
		QPoint endpt(mapLine[i].end.x,mapLine[i].end.y);
		painter.drawLine(startpt, endpt);
	}
	mapView->setPixmap(p);
}

void RobotDialog::getRoute()
{
// Step 1. Delete the lines that intersect with the map
	unsigned int k=0;
	for(unsigned int i=0; i<33; i++){
		for(unsigned int j=i+1; j<33; j++)
		{
			while(k<mapLine.size())
			{
				if (CrossPoint(mapLine[k], cornerpoint[i], cornerpoint[j]))
					k=mapLine.size()+1;
				else k++;
			}
			if(k==mapLine.size())
			{
				LinePos lp;
				lp.start=cornerpoint[i];
				lp.end=cornerpoint[j];
				routeLine.push_back(lp);
			}
			k=0;
		}}
	printf("Router Number: %d\n",routeLine.size());
// Step 2. Delete the lines that inside polygon
	vector<PointPos> polycorner;
	vector<LinePos> polyedge;
	int flags[cornerpoint.size()];

	for(unsigned int i=0; i<cornerpoint.size(); i++)
	{
		int total=1;
		bool nostop=true;
		if(flags[i]==1) continue;
		polycorner.push_back(cornerpoint[i]);
		flags[i]=1;
		int idxpoly=0;
		while(nostop)
		{
			for(unsigned int j=0; j<cornerpoint.size(); j++)
			{
				if(flags[j]==1) continue;
				for(unsigned int k=0; k<mapLine.size(); k++)
					if(ISSAME(mapLine[k], cornerpoint[j], polycorner[idxpoly]) || ISSAME(mapLine[k], polycorner[idxpoly], cornerpoint[j]))
					{
						polycorner.push_back(cornerpoint[j]);
						flags[j]=1; total++;
					}
			}
			idxpoly++;
			if(idxpoly==total)
				nostop=false;
		}
		sortCorner(polycorner);
 		if(polycorner.size()>3)		// If there are more than 3 point in a group, it is a polygon
 		{
			QPainter painter(&p);
			QBrush bluebrush(Qt::blue);
			painter.setBrush(bluebrush);
			for(unsigned int idp=0; idp<polycorner.size(); idp++)
				for(unsigned int idx=0; idx<polycorner.size(); idx++)
					for(unsigned int idr=0; idr<routeLine.size(); idr++)
						if(ISSAME(routeLine[idr], polycorner[idp], polycorner[idx]))
						{
							if(polySide(polycorner, routeLine[idr])) { routeLine.erase(routeLine.begin()+idr); break;}
						}
 		}
 		polycorner.clear();
 		polyedge.clear();
 	}
//Step 3. Delete all lines that through the circles
	int flag3[routeLine.size()];
	float small[STEPRATE-1];
	for(int i=0; i<STEPRATE-1; i++)
		small[i]=(i+1.0)/STEPRATE;
	for(unsigned int i=0; i<routeLine.size(); i++)
	{
		flag3[i]=0;
		int x1=routeLine[i].start.x;
		int y1=routeLine[i].start.y;
		int x2=routeLine[i].end.x;
		int y2=routeLine[i].end.y;
		for(int rate=0; rate<STEPRATE-1; rate++)
		{
			int x=(int)(small[rate]*x2+(1.0-small[rate])*x1);
			int y=(int)(small[rate]*y2+(1.0-small[rate])*y1);
			QRgb tmp=tmpImage.pixel(x, y);
			for(unsigned int j=0; j<centerP.size(); j++)
				if(tmp==centerP[j]) { flag3[i]=1; break; }
			if (flag3[i]==1) break;
		}
	}
	unsigned int tt=routeLine.size();
	for(unsigned int i=1; i<=tt; i++)
	{
		if(flag3[tt-i]==1)
			routeLine.erase(routeLine.begin()+(tt-i));
	}
// Step 4. Add all mapLine in routeLine
	for (unsigned int i=0; i<mapLine.size(); i++)
		routeLine.push_back(mapLine[i]);
	sortLine(routeLine);
	
	cout <<"Available route line number:" << routeLine.size()<<endl;
 	QPainter painter(&p);
	QPen redpen(Qt::red);
	redpen.setWidth(1);
	redpen.setStyle(Qt::DotLine);
	painter.setPen(redpen);
	for(unsigned int i=0;i<routeLine.size();i++)
	{
		QPoint startpt(routeLine[i].start.x,routeLine[i].start.y);
		QPoint endpt(routeLine[i].end.x,routeLine[i].end.y);
		painter.drawLine(startpt, endpt);
	}
	mapView->setPixmap(p);
}

float RobotDialog::distance(PointPos start, PointPos end)
{
	return sqrt(pow(start.y-end.y,2)+pow(start.x-end.x, 2));
}

void RobotDialog::paintEvent(QPaintEvent*)
{

}

int RobotDialog::CrossMutiply(PointPos P1,PointPos P2,PointPos P3)
{
	int p1[2],p2[2];
	int Result;
	static const int x = 0;
	static const int y = 1;
	p1[x] = P1.x - P2.x;
	p1[y] = P1.y - P2.y;
	p2[x] = P1.x - P3.x;
	p2[y] = P1.y - P3.y;
	Result = p1[x]*p2[y] - p1[y]*p2[x];
	if (Result>0)
		return 1;
	else if(Result <0)
		return -1;
	else
		return 0;
}

int RobotDialog::twoSide(PointPos P1, PointPos P2, PointPos P3, PointPos P4)
{
	int Signal1, Signal2;
	Signal1=CrossMutiply(P1, P2, P3);
	Signal2=CrossMutiply(P1, P2, P4);
	if(Signal1*Signal2<0)
		return 1;
	else
		return 0;
}

int RobotDialog::CrossPoint(LinePos L1, PointPos P1, PointPos P2)
{
	return twoSide(L1.start, L1.end, P1, P2)*twoSide(P1, P2, L1.start, L1.end);
}
// if the polygon is on one side of lp, return 0; else return 1
int RobotDialog::polySide(vector<PointPos> pt, LinePos lp)
{
	for (unsigned int i=0; i<pt.size()-1; i++)
		for (unsigned int j=i; j<pt.size(); j++)
			if(twoSide(lp.start, lp.end, pt[i], pt[j]))
				return 1;
	return 0;
}

bool RobotDialog::ISEQUAL(PointPos p1, PointPos p2)
{
	return (p1.x==p2.x)&&(p1.y==p2.y);
}
bool RobotDialog::ISSAME(LinePos L1, LinePos L2)
{
	return (ISEQUAL(L1.start, L2.start)&&ISEQUAL(L1.end, L2.end));
}
bool RobotDialog::ISSAME(LinePos L1, PointPos p1, PointPos p2)
{
	return (ISEQUAL(L1.start, p1)&&ISEQUAL(L1.end, p2));
}
void RobotDialog::FindShortest(int StartPoint,int EndPoint)
{
	int matrix_temp[33][33]={{INFINITY_G}};
	unsigned int i;
	for(i=0;i<routeLine.size();i++)
	{
		matrix_temp[routeLine[i].start.id][routeLine[i].end.id]=(int)routeLine[i].length;
		matrix_temp[routeLine[i].end.id][routeLine[i].start.id]=(int)routeLine[i].length;
	}
	matrix_temp[6][9]=0;
	matrix_temp[9][9]=0;
	matrix_temp[6][8]=0;
	matrix_temp[8][6]=0;
	matrix_temp[10][9]=0;
	matrix_temp[9][10]=0;
	matrix_temp[5][9]=0;
	matrix_temp[9][5]=0;
	matrix_temp[5][8]=0;
	matrix_temp[8][5]=0;
	for(int t=22;t<26;t++)
		for(int tt=22;tt<26;tt++)
			if(t!=tt)
				matrix_temp[t][tt] = 0;

	Graphm Gra(33, & matrix_temp[0][0]);
 	ShortestPath Path;
 	int * recordedpath;
  	recordedpath=new int[Gra.numVertex];
  	for (int i=0;i<Gra.numVertex;i++)
     		recordedpath[i]=0;
  	int length;
 	Path.Dijkstra(Gra,StartPoint,length,recordedpath,EndPoint);
// 	cout<<"The length of the path is:"<<length<<endl;
//   	cout<<"The index of the path is:";	
 	for(int i=0;i<length;i++)
    		cout<<recordedpath[i]<<" ";
  	cout<<endl;
	//draw lines
        QPainter painter(&p);
	QPen redpen(Qt::red);
	redpen.setWidth(5);
//	redpen.setStyle(Qt::DashDotLine);
	painter.setPen(redpen);
	for(int i=0; i<length-1; i++)
	{
		QPoint corneri(cornerpoint[recordedpath[i]].x,cornerpoint[recordedpath[i]].y);
		QPoint cornerj(cornerpoint[recordedpath[i+1]].x, cornerpoint[recordedpath[i+1]].y);
		painter.drawLine(corneri,cornerj);	
	}
	mapView->setPixmap(p);

 	
}
