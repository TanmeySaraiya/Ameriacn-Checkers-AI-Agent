#include<fstream>
#include<chrono>
#include<string>
#include<vector>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

char ply,plyk,opp,oppk;

bool is_moves_left_black(vector<vector<char>> bo){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(bo[i][j]=='b'){
                //E movement
                if((j-1>=0) && bo[i+1][j-1]=='.') return true;
                if((j+1<=7) && bo[i+1][j+1]=='.') return true;
                //J movement
                if((j-2>=0) && (i+2<=7) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.') return true;
                if((j+2<=7) && (i+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.') return true;
            }
            if(bo[i][j]=='B'){
                //E movement
                if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.') return true;
                if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.') return true;
                if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.') return true;
                if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.') return true;
                //J movement
                if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='w'||bo[i-1][j-1]=='W') && bo[i-2][j-2]=='.') return true;
                if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='w'||bo[i-1][j+1]=='W') && bo[i-2][j+2]=='.') return true;
                if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.') return true; 
                if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='w') && bo[i+2][j+2]=='.') return true;
            }
        }
    }
    return false;
}

bool is_moves_left_white(vector<vector<char>> bo){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(bo[i][j]=='w'){
                //E movement
                if((j-1>=0) && bo[i-1][j-1]=='.') return true;
                if((j+1<=7) && bo[i-1][j+1]=='.') return true;
                //J movement 
                if((j-2>=0) && (i-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.') return true;
                if((j+2<=7) && (i-2>=0) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.') return true;
            }
            if(bo[i][j]=='W'){
                //E movement
                if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.') return true;
                if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.') return true;
                if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.') return true;
                if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.') return true;
                //J movement
                if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.') return true;
                if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.') return true;
                if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='b'||bo[i+1][j-1]=='B') && bo[i+2][j-2]=='.') return true;
                if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='b'||bo[i+1][j+1]=='B') && bo[i+2][j+2]=='.') return true;
            }
        }
    }
    return false;
}

int evaluate(vector<vector<char>> bo){
    int points=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(bo[i][j]!='.'){
                if(bo[i][j]==ply){
                    points+=5;
                    if(j>2 && j<6) points+=3;
                    if(ply=='w'){
                        if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]==opp||bo[i-1][j-1]==oppk) && bo[i-2][j-2]=='.') points+=3;
                        if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]==opp||bo[i-1][j+1]==oppk) && bo[i-2][j+2]=='.') points+=3;
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.') points+=1;
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.') points+=1;

                        if(i<3) points+=2;

                    }
                    if(ply=='b'){
                        if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]==opp||bo[i+1][j-1]==oppk) && bo[i+2][j-2]=='.') points+=3;
                        if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]==opp||bo[i+1][j+1]==oppk) && bo[i+2][j+2]=='.') points+=3;
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.') points+=1;
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.') points+=1;
                        
                        if(i>4) points+=2;
                    }
                }
                else if (bo[i][j]==plyk)
                {
                    if(j>2 && j<6) points+=6;
                    points+=10;
                    if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]==opp||bo[i-1][j-1]==oppk) && bo[i-2][j-2]=='.') points+=3;
                    if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]==opp||bo[i-1][j+1]==oppk) && bo[i-2][j+2]=='.') points+=3;
                    if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]==opp||bo[i+1][j-1]==oppk) && bo[i+2][j-2]=='.') points+=3;
                    if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]==opp||bo[i+1][j+1]==oppk) && bo[i+2][j+2]=='.') points+=3;
                    
                    if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.') points+=1;
                    if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.') points+=1;
                    if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.') points+=1;
                    if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.') points+=1;
                    
                }
                else if (bo[i][j]==opp)
                {
                    if(j>2 && j<6) points-=3;
                    points-=5;
                    if(opp=='w'){
                        if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]==ply||bo[i-1][j-1]==plyk) && bo[i-2][j-2]=='.') points-=3;
                        if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]==ply||bo[i-1][j+1]==plyk) && bo[i-2][j+2]=='.') points-=3;
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.') points-=1;
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.') points-=1;

                        if(i<3) points-=2;
                    }
                    if(opp=='b'){
                        if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]==ply||bo[i+1][j-1]==plyk) && bo[i+2][j-2]=='.') points-=3;
                        if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]==ply||bo[i+1][j+1]==plyk) && bo[i+2][j+2]=='.') points-=3;
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.') points-=1;
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.') points-=1;

                        if(i>4) points-=2;
                    }
                }
                else if (bo[i][j]==oppk)
                {
                    if(j>2 && j<6) points-=6;
                    points-=10;
                    if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]==ply||bo[i-1][j-1]==plyk) && bo[i-2][j-2]=='.') points-=3;
                    if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]==ply||bo[i-1][j+1]==plyk) && bo[i-2][j+2]=='.') points-=3;
                    if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]==ply||bo[i+1][j-1]==plyk) && bo[i+2][j-2]=='.') points-=3;
                    if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]==ply||bo[i+1][j+1]==plyk) && bo[i+2][j+2]=='.') points-=3;
                    if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.') points-=1;
                    if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.') points-=1;
                    if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.') points-=1;
                    if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.') points-=1;

                }
            }
        }
    }
    return points;
}

vector<vector<char>> change_board_jump(vector<vector<char>> bo,int i,int j, int c,int d){
    bo[c][d]=bo[i][j];
    bo[i][j]='.';
    bo[(i+c)/2][(j+d)/2]='.';
    if(bo[c][d]=='b' && c==7) bo[c][d]='B';
    if(bo[c][d]=='w' && c==0) bo[c][d]='W';
    return bo;
}

vector<vector<char>> change_board_e(vector<vector<char>> bo,int i,int j,int c,int d){
    bo[c][d]=bo[i][j];
    bo[i][j]='.';
    if(bo[c][d]=='w' && c==0) bo[c][d]='W';
    if(bo[c][d]=='b' && c==7) bo[c][d]='B';
    return bo;
}

vector<vector<int>> jumps_done(vector<vector<char>> bo,int i,int j){
    vector<int> path_latest;
    int flag=0;
    path_latest.push_back(i);
    path_latest.push_back(j);
    vector<int> store_temp;
    vector<vector<int>> paths_temp;
    vector<vector<int>> paths_give;
    if(bo[i][j]=='w'){
        if((j-2>=0) && (i-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.'){
            flag=1;
            if(i-2!=0){
                paths_temp=jumps_done(change_board_jump(bo,i,j,i-2,j-2),i-2,j-2);
                for(auto x:paths_temp){
                    store_temp=path_latest;
                    store_temp.insert(store_temp.end(),x.begin(),x.end());
                    paths_give.push_back(store_temp);
                }
            }
            else{
                store_temp=path_latest;
                store_temp.push_back(i-2);
                store_temp.push_back(j-2);
                paths_give.push_back(store_temp);
            }
        }  
        if((j+2<=7) && (i-2>=0) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.'){
            flag=1;
            if(i-2!=0){
                paths_temp=jumps_done(change_board_jump(bo,i,j,i-2,j+2),i-2,j+2);
                for(auto x:paths_temp){
                    store_temp=path_latest;
                    store_temp.insert(store_temp.end(),x.begin(),x.end());
                    paths_give.push_back(store_temp);
                }
            }
            else{
                store_temp=path_latest;
                store_temp.push_back(i-2);
                store_temp.push_back(j+2);
                paths_give.push_back(store_temp);
            }
        }
    }                
    else if(bo[i][j]=='W'){
        if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i-2,j-2),i-2,j-2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            }            
        }
        if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i-2,j+2),i-2,j+2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            }        
        }
        if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='b'||bo[i+1][j-1]=='B') && bo[i+2][j-2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i+2,j-2),i+2,j-2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            }        
        }
        if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='b'||bo[i+1][j+1]=='B') && bo[i+2][j+2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i+2,j+2),i+2,j+2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            } 
        }
    }
    else if(bo[i][j]=='b'){
        if((j-2>=0) && (i+2<=7) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.'){
            flag=1;
            if(i+2!=7){
                paths_temp=jumps_done(change_board_jump(bo,i,j,i+2,j-2),i+2,j-2);
                for(auto x:paths_temp){
                    store_temp=path_latest;
                    store_temp.insert(store_temp.end(),x.begin(),x.end());
                    paths_give.push_back(store_temp);
                }
            }
            else{
                store_temp=path_latest;
                store_temp.push_back(i+2);
                store_temp.push_back(j-2);
                paths_give.push_back(store_temp);
            }
        }
        if((j+2<=7) && (i+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.'){
            flag=1;
            if(i-2!=0){
                paths_temp=jumps_done(change_board_jump(bo,i,j,i+2,j+2),i+2,j+2);
                for(auto x:paths_temp){
                    store_temp=path_latest;
                    store_temp.insert(store_temp.end(),x.begin(),x.end());
                    paths_give.push_back(store_temp);
                }
            }
            else{
                store_temp=path_latest;
                store_temp.push_back(i+2);
                store_temp.push_back(j+2);
                paths_give.push_back(store_temp);
            }
        }
    }
    else if(bo[i][j]=='B'){
        if((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='w'||bo[i-1][j-1]=='W') && bo[i-2][j-2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i-2,j-2),i-2,j-2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            } 
        }
        if((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='w'||bo[i-1][j+1]=='W') && bo[i-2][j+2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i-2,j+2),i-2,j+2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            } 
        }
        if((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i+2,j-2),i+2,j-2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            } 
        }
        if((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.'){
            flag=1;
            paths_temp=jumps_done(change_board_jump(bo,i,j,i+2,j+2),i+2,j+2);
            for(auto x:paths_temp){
                store_temp=path_latest;
                store_temp.insert(store_temp.end(),x.begin(),x.end());
                paths_give.push_back(store_temp);
            }             
        }
    }
    if(flag==0){
        paths_give.push_back(path_latest);
    }

    return  paths_give;
}

int maxi(vector<vector<char>> bo,int d,int h,int alpha,int beta);

int mini(vector<vector<char>> bo,int d, int h,int alpha,int beta){
    if(d==h){return evaluate(bo);}
    if(opp=='b'){
        if(!is_moves_left_black(bo)){
            return 50;
        }
    }
    else if(opp=='w'){
        if(!is_moves_left_white(bo)){
            return 50;
        }
    }
    vector<vector<int>> moves;
    vector<vector<int>> temp;
    vector<vector<char>> bo_temp;
    int min_val=INT_MAX;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((bo[i][j]==opp||bo[i][j]==oppk) && opp=='b'){
                if(bo[i][j]=='b'){
                    if(((j-2>=0) && (i+2<=7) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.')
                     ||((j+2<=7) && (i+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
                if(bo[i][j]=='B'){
                    if(((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='w'||bo[i-1][j-1]=='W') && bo[i-2][j-2]=='.')
                     ||((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='w'||bo[i-1][j+1]=='W') && bo[i-2][j+2]=='.')
                     ||((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.')
                     ||((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
            }
            if((bo[i][j]==opp||bo[i][j]==oppk) && opp=='w'){
                if(bo[i][j]=='w'){
                    if(((j-2>=0) && (i-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.')
                     ||((j+2<=7) && (i-2>=0) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
                if(bo[i][j]=='W'){
                    if(((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.')
                     ||((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.')
                     ||((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='b'||bo[i+1][j-1]=='B') && bo[i+2][j-2]=='.')
                     ||((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='b'||bo[i+1][j+1]=='B') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
            }
        }
    }
    if(moves.size()!=0){
        for(auto m:moves){
            bo_temp=bo;
            for(int a=0;a< m.size()-3;a+=2){
                bo_temp=change_board_jump(bo_temp,m[a],m[a+1],m[a+2],m[a+3]);
            }
            min_val=min(min_val,maxi(bo_temp,d+1,h,alpha,beta));
            if(min_val<=alpha){
                return min_val;                             
            }
            beta=min(beta,min_val);
        }
    return min_val;
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if((bo[i][j]==opp||bo[i][j]==oppk) && opp=='b'){
                    if(bo[i][j]=='b'){
                        if((j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                    if(bo[i][j]=='B'){
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});
                        }
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                }
                if((bo[i][j]==opp||bo[i][j]==oppk) && opp=='w'){
                    if(bo[i][j]=='w'){
                        if((j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});
                        }
                    }
                    if(bo[i][j]=='W'){
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.'){
                            //cout<<i-1<<" "<<j-1<<endl;
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.'){
                            //cout<<i-1<<" "<<j+1<<endl;
                            moves.push_back({i,j,i-1,j+1});
                        }
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.'){
                            //cout<<i+1<<" "<<j-1<<endl;
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.'){
                            //cout<<i+1<<" "<<j+1<<endl;
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                }
            }   
        }
    }
    if(moves.size()!=0){
        for(auto m:moves){
            bo_temp=change_board_e(bo,m[0],m[1],m[2],m[3]);
            min_val=min(min_val,maxi(bo_temp,d+1,h,alpha,beta));
            if(min_val<=alpha){
                return min_val;                             
            }
            beta=min(beta,min_val);
        }
    }
    else{
        return 30;
    }
    return min_val;
}

int maxi(vector<vector<char>> bo,int d,int h,int alpha,int beta){
    if(d==h){ return evaluate(bo);}
    if(ply=='b'){
        if(!is_moves_left_black(bo)){
            return -50;
        }
    }
    else if(ply=='w'){
        if(!is_moves_left_white(bo)){
            return -50;
        }
    }
    vector<vector<int>> moves;
    vector<vector<int>> temp;
    vector<vector<char>> bo_temp;
    int max_val=INT_MIN;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='b'){
                if(bo[i][j]=='b'){
                    if(((j-2>=0) && (i+2<=7) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.')
                     ||((j+2<=7) && (i+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
                if(bo[i][j]=='B'){

                    if(((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='w'||bo[i-1][j-1]=='W') && bo[i-2][j-2]=='.')
                     ||((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='w'||bo[i-1][j+1]=='W') && bo[i-2][j+2]=='.')
                     ||((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.')
                     ||((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
            }
            if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='w'){
                if(bo[i][j]=='w'){
                    if(((j-2>=0) && (i-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.')
                     ||((j+2<=7) && (i-2>=0) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
                if(bo[i][j]=='W'){
                    if(((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.')
                     ||((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.')
                     ||((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='b'||bo[i+1][j-1]=='B') && bo[i+2][j-2]=='.')
                     ||((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='b'||bo[i+1][j+1]=='B') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
            }
        }
    }
    if(moves.size()!=0){
        for(auto m:moves){
            bo_temp=bo;
            for(int a=0;a<m.size()-3;a+=2){
                bo_temp=change_board_jump(bo_temp,m[a],m[a+1],m[a+2],m[a+3]);
            }
            max_val=max(max_val,mini(bo_temp,d+1,h,alpha,beta));
            if(max_val>=beta){
                return max_val;
            }
            alpha=max(alpha,max_val);
        }
    return max_val;
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='b'){
                    if(bo[i][j]=='b'){
                        if((j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                    if(bo[i][j]=='B'){
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});
                        }
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                }
                if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='w'){
                    if(bo[i][j]=='w'){
                        if((j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});
                        }
                    }
                    if(bo[i][j]=='W'){
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});     
                        }
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                }
            }   
        }
    }
    if(moves.size()!=0){
        for(auto m:moves){
            bo_temp=change_board_e(bo,m[0],m[1],m[2],m[3]);
            max_val=max(max_val,mini(bo_temp,d+1,h,alpha,beta));
            if(max_val>=beta){
                return max_val;
            }
            alpha=max(alpha,max_val);
        }
    }
    else{ 
        return -30;}
    return max_val;
}

string minimax(vector<vector<char>> bo,int d,int h){
    vector<vector<int>> moves;
    vector<vector<int>> temp;
    vector<vector<char>> bo_temp;
    vector<int> move_top;
    string move_make="";
    int max_val=INT_MIN;
    int alpha=INT_MIN;
    int beta=INT_MAX;
    int temp_score;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='b'){
                if(bo[i][j]=='b'){
                    if(((j-2>=0) && (i+2<=7) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.')
                     ||((j+2<=7) && (i+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
                if(bo[i][j]=='B'){
                    if(((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='w'||bo[i-1][j-1]=='W') && bo[i-2][j-2]=='.')
                     ||((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='w'||bo[i-1][j+1]=='W') && bo[i-2][j+2]=='.')
                     ||((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='w'||bo[i+1][j-1]=='W') && bo[i+2][j-2]=='.')
                     ||((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='w'||bo[i+1][j+1]=='W') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }

                }
            }
            if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='w'){
                if(bo[i][j]=='w'){
                    if(((j-2>=0) && (i-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.')
                     ||((j+2<=7) && (i-2>=0) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
                if(bo[i][j]=='W'){
                    if(((i-2>=0) && (j-2>=0) && (bo[i-1][j-1]=='b'||bo[i-1][j-1]=='B') && bo[i-2][j-2]=='.')
                     ||((i-2>=0) && (j+2<=7) && (bo[i-1][j+1]=='b'||bo[i-1][j+1]=='B') && bo[i-2][j+2]=='.')
                     ||((i+2<=7) && (j-2>=0) && (bo[i+1][j-1]=='b'||bo[i+1][j-1]=='B') && bo[i+2][j-2]=='.')
                     ||((i+2<=7) && (j+2<=7) && (bo[i+1][j+1]=='b'||bo[i+1][j+1]=='B') && bo[i+2][j+2]=='.')){
                        temp=jumps_done(bo,i,j);
                        moves.insert(moves.end(),temp.begin(),temp.end());
                    }
                }
            }
        }
    }
    if(moves.size()!=0){
        for(auto m:moves){
            bo_temp=bo;
            for(int a=0;a<m.size()-3;a+=2){
                bo_temp=change_board_jump(bo_temp,m[a],m[a+1],m[a+2],m[a+3]);
            }
            temp_score=mini(bo_temp,d+1,h,alpha,beta);
            if(temp_score>max_val){
                move_top=m;
                max_val=temp_score;
            }
            if(max_val>=beta) break;
            alpha=max(alpha,max_val);
        }
        for(int i=0;i<move_top.size()-3;i+=2){
            move_make=move_make+"J "+string(1,char('a'+move_top[i+1]))+string(1,char('0'+(8-move_top[i])))+' '+string(1,char('a'+move_top[i+3]))+string(1,char('0'+(8-move_top[i+2])))+'\n';
        }
        return move_make;
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='b'){
                    if(bo[i][j]=='b'){
                        if((j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                    if(bo[i][j]=='B'){
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});
                        }
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                }
                if((bo[i][j]==ply||bo[i][j]==plyk) && ply=='w'){
                    if(bo[i][j]=='w'){
                        if((j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});
                        }
                    }
                    if(bo[i][j]=='W'){
                        if((i-1>=0) && (j-1>=0) && bo[i-1][j-1]=='.'){
                            moves.push_back({i,j,i-1,j-1});
                        }
                        if((i-1>=0) && (j+1<=7) && bo[i-1][j+1]=='.'){
                            moves.push_back({i,j,i-1,j+1});     
                        }
                        if((i+1<=7) && (j-1>=0) && bo[i+1][j-1]=='.'){
                            moves.push_back({i,j,i+1,j-1});
                        }
                        if((i+1<=7) && (j+1<=7) && bo[i+1][j+1]=='.'){
                            moves.push_back({i,j,i+1,j+1});
                        }
                    }
                }
            }   
        }
    }
    if(moves.size()!=0){
        for(auto m:moves){
            bo_temp=change_board_e(bo,m[0],m[1],m[2],m[3]);
            temp_score=mini(bo_temp,d+1,h,alpha,beta);
            if(temp_score>max_val){
                max_val=temp_score;
                move_top=m;
            }
            if(max_val>=beta) break;
            alpha=max(alpha,max_val);
        }

        move_make="E "+string(1,char('a'+move_top[1]))+string(1,char('0'+(8-move_top[0])))+' '+string(1,char('a'+move_top[3]))+string(1,char('0'+(8-move_top[2])))+'\n';
    }
    return move_make;
}

int main(){
    vector<vector<char>> board
    {
        {'.','b','.','b','.','b','.','b'},
        {'b','.','b','.','B','.','b','.'},
        {'.','.','.','.','.','b','.','.'},
        {'.','B','.','b','.','.','.','B'},
        {'w','.','.','.','.','W','.','.'},
        {'.','.','w','W','w','.','W','.'},
        {'.','w','.','.','.','.','.','w'},
        {'w','.','w','.','w','.','w','.'}    
    };
    ply='w';
    plyk='W';
    opp='b';
    oppk='B';
    remove("calibration.txt");
    ofstream cali;
    string move;
    cali.open("calibration.txt");
    auto start = chrono::high_resolution_clock::now(); 
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);                                         
    for(int i=5;i<11;i++){
        start = chrono::high_resolution_clock::now();  
        move=minimax(board,0,i);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start); 
        cali<<duration.count();
        cali<<endl;
    }
    cali<<duration.count();
    return 0;
}

