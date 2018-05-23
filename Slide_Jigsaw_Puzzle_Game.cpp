/*
 * @Author: Liuyang Jiang 
 * @Date: 2018-03-30 16:40:52 
 * @Description: 
 * @Coding: utf-8
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <stdlib.h> 
#include <process.h>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;

void swap(int *x, int *y) {
	int temp;	
	temp = *x;	
	*x = *y;
	*y = temp;
}

class Plate
{
public:
    Plate(int N,int M){
        n = N;
        m = M;
        for(int i=0;i<n*m;i++){
            data.push_back(i);
        }
        srand(time(NULL));
        int p;
	    for(int i=0;i<n*m;i++) {
		    p=random(i,n*m-1);
		    swap(data[i],data[p]);
	    }
    }
    ~Plate(){}
    Plate(const Plate&p){}

    bool left(){
        for(int i=0;i<n*m;i++){
            if(data[i]==0){
                if(i%m==m-1){
                    cout<<"ERROR"<<endl;
                    break;
                }
                else {
                    swap(data[i],data[i+1]);
                    showplate();
                    break;
                }
            }
        }
        if(iswin() == true)return true;
        else return false;
    }
    bool right(){
        for(int i=0;i<n*m;i++){
            if(data[i]==0){
                if(i%m==0){
                    cout<<"ERROR"<<endl;
                    break;
                }
                else {
                    swap(data[i],data[i-1]);
                    showplate();
                    break;
                }
            }
        }
        if(iswin() == true)return true;
        else return false;
    }
    bool upward(){
        for(int i=0;i<n*m;i++){
            if(data[i]==0){
                if(i>=n*m-m){
                    cout<<"ERROR"<<endl;
                    break;
                }
                else {
                    swap(data[i],data[i+m]);
                    showplate();
                    break;
                }
            }
        }
        if(iswin() == true)return true;
        else return false;
    }
    bool downward(){
        for(int i=0;i<n*m;i++){
            if(data[i]==0){
                if(i<m){
                    cout<<"ERROR"<<endl;
                    break;
                }
                else {
                    swap(data[i],data[i-m]);
                    showplate();
                    break;
                }
            }
        }
        if(iswin() == true)return true;
        else return false;
    }
    void showplate(){
        system("cls");
        for(int i=0;i<n;i++)
        {
            for(int k=0;k<5;k++){
                for(int j=0;j<m;j++){
                    if(k==0||k==4){
                        if(data[i*m+j]!=0)
                            cout<<"o----o ";
                        else cout<<"       ";
                    }
                    else if(k==1||k==3){
                        if(data[i*m+j]!=0)
                            cout<<"|    | ";
                        else cout<<"       ";
                    }
                    else {
                        if(data[i*m+j]!=0)
                        {
                            cout<<"| ";
                            if(data[i*m+j]<10)cout<<" ";
                            cout<<data[i*m+j]<<" | ";
                        }
                        else cout<<"       ";
                    }
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }
    bool iswin(){
        for(int i=0;i<n*m-1;i++){
            if(data[i]!=i+1)return false;
        }
        return true;
    }

private:
    int n,m;
    vector<int> data;
};

void printmenu(){
    system("cls");
    cout<<"Welcome to the Slide Jigsaw Puzzle Game."<<endl;
    cout<<"Here are the rules: "<<endl;
    cout<<"You can enter two numbers n and m to determine the rows and columns of the board."<<endl
        <<"And each element of the board will be assigned by a number between 0 to n*m-1."<<endl
        <<"You can press the arrow keys to move the element in the board."<<endl
        <<"Your goal is to place the numbers in corresponding positions."<<endl
        <<"Now,have fun with the game!"<<endl;
    return;
}

int select()
{
    char key, key2;
    bool needNextKey = false;
    while( ( key = _getch() ) != 27 ) //press ESC to break
    {
        if( needNextKey )
        {
            if( key2 == -32 )
            {
                if( key == 75 ) //left
                {
                    //cout<<"<--"<<endl;
                    return 1;
                }
                else if( key == 77 ) //right
                {
                    //cout<<"-->"<<endl;
                    return 2;
                }
                else if( key == 72 )//up
                {
                    //cout<<"^"<<endl<<"|"<<endl;
                    return 3;
                }
                else if( key == 80)//down
                {
                    //cout<<"|"<<endl<<"v"<<endl;
                    return 4;
                }
            }
            needNextKey = false;
        }
        if( key <= 0 )
        {
            key2 = key;
            needNextKey = true;
        }
    }
    return 0;
}
int main(){
    int n,m;
    bool res=false;
    int num=0;
    char ch;
    printmenu();
    cout<<"Please enter the size of the board: ";
    cin>>n>>m;
    Plate pl(n,m);
    pl.showplate();
    while(true){
        num++;
        switch(select())
        {
            case 1:res = pl.left();break;
            case 2:res = pl.right();break;
            case 3:res = pl.upward();break;
            case 4:res = pl.downward();break;
            case 0:
                cout<<"Do you really want to quit the game?( y | n )"<<endl;
                ch = _getch();
                if(ch == 'y'){
                    cout<<"Thank you !!"<<endl;
                    return 0;
                }
                else break;
        }
        if(res == true){
            cout<<endl<<"Congratulations!"<<endl<<"You have complete the the Slide Jigsaw Puzzle Game with "<<num<<" steps."<<endl;
            break;
        }
    }
    return 0;
}
