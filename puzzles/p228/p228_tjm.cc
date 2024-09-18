#include<iostream>
//Brute force solution for "Lights Out" game
int main(){
const int N = 5;

// build matrix of possible moves
int moves[N*N];
for (int ridx=0;ridx<N;ridx++){
    for (int cidx=0;cidx<N;cidx++){
        int move =  1<<(ridx*N+cidx);
        if (ridx > 0)
            move += 1<<((ridx-1)*N+cidx);
        if (ridx < N-1)
            move += 1<<((ridx+1)*N+cidx);
        if (cidx > 0)
            move += 1<<(ridx*N+cidx-1);
        if (cidx < N-1)
            move += 1<<(ridx*N+cidx+1);
        moves[ridx*N+cidx] = move;
    }
}

for (int st =10;st<30;st++){
    bool solved = false;
    std::cout << " st " << st << " ";
    //try all 2^25 moves for this starting state
    for(int mvs =0;mvs < 1<<(N*N); mvs++){
        int tmp = st;
        for(int midx =0;midx<N*N;midx++){
            if (mvs & (1<< midx))
                tmp = tmp ^ moves[midx];
        }
        if (tmp == 0){
            solved = true;
            std::cout << "solved";
            break;
        }
    }
    std::cout << std::endl;
}

// start in the "solved state" and keep track of all the end states from all possible moves
std::vector<char> all(1<<(N*N),0);
//try all 2^25 moves for this starting state
for(int mvs =0;mvs < 1<<(N*N); mvs++){
    int tmp = 0;
    for(int midx =0;midx<N*N;midx++){
        if (mvs & (1<< midx))
            tmp = tmp ^ moves[midx];
    }
    all[tmp]+=1;
}

int cnt=0;
for(int mvs =0;mvs < 1<<(N*N); mvs++){
    if(all[mvs])
        cnt++;
}
std::cout << " cnt is " << cnt << std::endl;  ;

std::cout << std::endl;

}


