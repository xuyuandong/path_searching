#ifndef ROBOTDIALOG_H
#define ROBOTDIALOG_H

#include <QDialog>
#include <qfiledialog.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qimage.h>
#include <QColor>
#include <QPainter>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include "ui_robotdialog.h"
#include <vector>
#include <math.h>
using namespace std;

typedef struct Point{
	int x;
	int y;
	int id;
}PointPos;

typedef struct Line{
	PointPos start;
	PointPos end;
	float length;
}LinePos;


class RobotDialog : public QDialog, public Ui::RobotDialog
{
	Q_OBJECT

public:
	RobotDialog(QWidget *parent = 0);
	void getCorner(const QString & image);
	void drawCorner();
	void sortCorner(vector<PointPos>& corner);
	void sortLine(vector<LinePos>& line);
	void drawRoute();
	void houghMap(const QString & image);
	void fitMap();
	float distance(PointPos start, PointPos end);
	void getRoute();
	int CrossMutiply(PointPos P1,PointPos P2,PointPos P3);
	int twoSide(PointPos P1, PointPos P2, PointPos P3, PointPos P4);
	int polySide(vector<PointPos> pt, LinePos lp);
	int CrossPoint(LinePos L1, PointPos P1, PointPos P2);
	bool ISEQUAL(PointPos p1, PointPos p2);
	bool ISSAME(LinePos L1, LinePos L2);
	bool ISSAME(LinePos L1, PointPos p1, PointPos p2);
        void FindShortest(int StartPoint,int EndPoint);
public slots:
	void mapOpen();
	void nextStep();
	void paintEvent(QPaintEvent*);
public:
	QString imageName;
private:
	int stepNumber;
	int cornerNumber;
	QImage tmpImage;
	QPixmap lastpixmap;
	vector<QRgb> centerP;
	vector<LinePos> houghLine;
	vector<LinePos> mapLine;
public:
	QPixmap p;
	vector<PointPos> cornerpoint;
	vector<LinePos> routeLine;
	vector<PointPos> ptStart;
	vector<PointPos> ptEnd;
};

#endif
