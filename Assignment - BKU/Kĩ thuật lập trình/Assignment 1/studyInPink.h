/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2022
    * Author: Tran Huy
    * Date: 06.01.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int resetEX(int &x){
	if(x<0)
		x=0;
	if(x>900)
		x=900;
	return x;
}
int resetHP(int &x){
	if(x<0)
		x=0;
	if(x>999)
		x=999;
	return x;
}
int resetM(int &x){
	if(x<0)
		x=0;
	if(x>2000)
		x=2000;
	return x;
}
int firstMeet(int& EXP1, int& EXP2, const int& E1){
    //Complete this function to gain point on task 1
    if(E1<400 && E1>=0){
		if(E1>=0 && E1<=49)
			EXP2+=25;
		if(E1>=50 && E1<=99)
			EXP2+=50;
		if(E1>=100 && E1<=149)
			EXP2+=85;
		if(E1>=150 && E1<=199)
			EXP2+=75;
		if(E1>=200 && E1<=249)
			EXP2+=110;
		if(E1>=250 && E1<=299)
			EXP2+=135;
		if(E1>=300 && E1<=399)
			EXP2+=160;
		EXP2=resetEX(EXP2);
		if(E1%2==1)
			{EXP1=ceil(EXP1+E1/10.0);
			EXP1=resetEX(EXP1);}
		else
			{EXP1=ceil(EXP1-E1/5.0);
			EXP1=resetEX(EXP1);}
		return (EXP1 + EXP2);
	}else if(E1>=400 && E1<=999){
		if(E1>=400 && E1<=499)
			EXP2=ceil(EXP2+(E1/7.0+9));
		if(E1>=500 && E1<=599)
			EXP2=ceil(EXP2+(E1/9.0+11));
		if(E1>=600 && E1<=699)
			EXP2=ceil(EXP2+(E1/5.0 +6));
		if(E1>=700 && E1<=799){
			EXP2=ceil(EXP2+(E1/7.0+9));
			if(EXP2>200)
				EXP2=ceil(EXP2+(E1/9.0+11));
		}
		if(E1>=800 && E1<=999){
			EXP2=ceil(EXP2+ E1/7.0+9);
			EXP2=ceil(EXP2+ E1/9.0+11);
			if(EXP2>600){
				EXP2=ceil(EXP2+(E1/5.0+6));
				EXP2=ceil(EXP2*1.15);
			}
		}
		EXP2=resetEX(EXP2);
		EXP1=ceil(EXP1-0.1*E1);
		EXP1=resetEX(EXP1);
		return(EXP1+EXP2);
	}else
		return -999;
    return -1;
}

int investigateScene(int& EXP1, int& EXP2, int& HP2, int& M2, const int& E2){
    //Complete this function to gain point on task 2
    if(E2>=0 && E2<=299){
		EXP2=ceil(EXP2+(E2/9.0+10));
		EXP1=ceil(EXP1+(E2/9.0+10)/3);
	}
	else if(E2>=300 && E2<=499){
		EXP2=ceil(EXP2+(E2/9.0+10));
		EXP1=ceil(EXP1+(E2/9.0+10)/3);
		EXP1=resetEX(EXP1);
		EXP2=resetEX(EXP2);
		EXP2+=ceil(0.35*E2);
		EXP1+=ceil(0.35*E2/3);
	}
	else if(E2>=500 && E2<=999){
		EXP2=ceil(EXP2+(E2/9.0+10));
		EXP1=ceil(EXP1+(E2/9.0+10)/3);
		EXP1=resetEX(EXP1);
		EXP2=resetEX(EXP2);
		EXP2+=ceil(0.35*E2);
		EXP1+=ceil(0.35*E2/3);
		EXP1=resetEX(EXP1);
		EXP2=resetEX(EXP2);
		EXP2+=ceil((E2/9.0+10+0.35*E2)*0.17);
		EXP1+=ceil((E2/9.0+10+0.35*E2)*0.17/3);
	}
	else
		return -999;
	EXP1=resetEX(EXP1);
	EXP2=resetEX(EXP2);
	HP2=ceil(HP2-(pow(E2,3))/pow(2,23));
	HP2=resetHP(HP2);
	if(E2%2==0){
		M2=ceil(M2+pow(E2,2)/50.0);
		M2=resetM(M2);
	}
	M2=resetM(M2);
	return (EXP1+EXP2+M2+HP2);
    return -1;
}

int traceLuggage(int& HP1, int& EXP1, int& M1, const int& E3){
    //Complete this function to gain point on task 3
    if(E3<0 || E3>999)
		return -999;
	else{
	int a1[9]={1,3,5,7,9,11,13,15,17};
	int a2[7]={2,3,5,7,11,13,17};
	int a3[20]={4,16,36,64,100,144,196,256,324,400,484,576,676,784,900,1024,1156,1296,1444,1600};
	int a4[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	//con duong 1
	int find1=0,find2=0,find3=0,find4=0,k;
	for(int i=0;i<9;i++){
		a1[i]=(a1[i]+E3)%26+65;
		if(a1[i]==80)
			k=i+1;
			HP1=HP1-80*k*2;
			EXP1=EXP1+(1000-80*k)%101;
			HP1=resetHP(HP1);
			EXP1=resetEX(EXP1);
			find1=1;
			break;
	}
	if(find1 == 1){
		M1=ceil(M1-(k*E3)/9.0);
		M1=resetM(M1);
	}else{
		M1=ceil(M1-(81*E3)/9.0);
		M1=resetM(M1);
	}
	//con duong 2
	int sum=0, tb=0;
	for(int i=0;i<7;i++){
		a2[i]=(a2[i]+E3)%26;
		sum=sum+a2[i];
	}
	tb=ceil(sum/7.0);
	for(int i=0;i<7;i++){
		a2[i]=(a2[i]+sum+tb)%26+65;
		if(a2[i]==80){
			k=i+1;
			HP1=HP1-80*k*2;
			EXP1=EXP1+(1000-80*k)%101;
			HP1=resetHP(HP1);
			EXP1=resetEX(EXP1);
			find2=1;
			break;
		}
	}
	if(find2 == 1){
		M1=ceil(M1-(k*E3)/9.0);
		M1=resetM(M1);
	}else{
		M1=ceil(M1-(49*E3)/9.0);
		M1=resetM(M1);
	}
	//con duong 3
	int max=0;
	for(int i=0;i<19;i++){
		a3[i]=(a3[i]+E3*E3)%113;
		if(a3[i]>max){
			max=a3[i];
		}
	}
	for(int i=19;i>=0;i--){
		a3[i]=ceil((a3[i]+E3)/(float)max);
		a3[i]=a3[i]%26+65;
		if(a3[i]==80){
			k=20-i;
			HP1=HP1-80*k*3;
			EXP1=EXP1+(3500-80*k)%300;
			HP1=resetHP(HP1);
			EXP1=resetEX(EXP1);
			find3=1;
			break;
		}
	}
	if(find3 == 1){
		M1=ceil(M1-(k*E3)/9.0);
		M1=resetM(M1);
	}else{
		M1=ceil(M1-(400*E3)/9.0);
		M1=resetM(M1);
	}
	//con duong 4
	int min=8,min_idx=0;
	int n=ceil(E3/29.0);
	for(int i=0;i<12;i++){
		a4[i]=ceil((a4[i]+n*n*n));
		a4[i]=a4[i]%9;
		if(a4[i]<min){
			min=a4[i];
			min_idx=i+1;
		}
	}
	for(int i=11;i>=0;i--){
		a4[i]=ceil((a4[i]+E3)*(min/(float)min_idx));
		a4[i]=a4[i]%26+65;
		if(a4[i]==80){
			k=12-i;
			HP1=HP1-80*k*4;
			EXP1=EXP1+(4500-80*k)%400;
			HP1=resetHP(HP1);
			EXP1=resetEX(EXP1);
			find4=1;
			break;
		}
	}
	if(find4 == 1){
		M1=ceil(M1-(k*E3)/9.0);
		M1=resetM(M1);
	}else{
		M1=ceil(M1-(144*E3)/9.0);
		M1=resetM(M1);
	}
	if(find1==0 && find2==0 && find3==0 && find4==0){
		HP1=HP1-(59*E3)%900;
		EXP1=EXP1-(79*E3)%300;
		HP1=resetHP(HP1);
		EXP1=resetEX(EXP1);
		return -1;
	}else
		return EXP1+M1+HP1;
}
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
