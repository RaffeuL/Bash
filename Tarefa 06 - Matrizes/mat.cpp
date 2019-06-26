#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
#define ordem 2 //Mudar a Ordem da Matriz
#define buf 256

int pipe(int filedes[2]);


using namespace std;

double matA[ordem][ordem];
double matB[ordem][ordem];

void preencher(double mat[][ordem]){
	for(int linha=0;linha<ordem;linha++){
    for(int coluna=0;coluna<ordem;coluna++) 
      cin >> mat[linha][coluna];
    cout << endl;
  }
}

void exibir(double mat[][ordem]){
	for(int linha=0;linha<ordem;linha++){
    for(int coluna=0;coluna<ordem;coluna++) 
      cout << setw(12)<< mat[linha][coluna];
    cout << endl;
  }
}

void cofator(double mat[ordem][ordem],double temp[ordem][ordem], int p, int q, int n){

  int i = 0, j = 0;

  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (row != p && col != q){
        temp[i][j] = mat[row][col];
        j++;
        if (j == n - 1){
          j = 0;
          i++;
        }
      }
    }
  }
}

int determinante(double mat[][ordem], int n){

  int D = 0;
   
  if (n == 1) return mat[0][0];
    
  double temp[ordem][ordem];
  int sign = 1;
    
  for (int f = 0; f < n; f++){
    cofator(mat, temp, 0, f, n);
    D += sign * mat[0][f] * determinante(temp, n - 1);
    sign = -sign;
  }
  return D;
}

int inversa(double mat[][ordem],int n){
  double det;
  int sign = 1;
  double temp[ordem][ordem];
  double inversa[ordem][ordem];
  
  det = determinante(mat,ordem);

  if (det == 0){
    cout << "A matriz n�o pode ser invertida" << endl;
    return 0;
  }
  
  for (int f = 0; f < n; f++){
    for(int g = 0; g < n; g++){
    	
    	if(((f+g)+2)% 2 == 0) sign = 1;
		else sign = -1;
		cofator(mat,temp,f,g,n); //matriz adjunta
		inversa[g][f]= (sign * (determinante(temp, n - 1)/det));
      
    }
  }
	for (int f = 0; f < n; f++){
    for(int g = 0; g < n; g++){
    	mat[f][g] = inversa[f][g];
    }
  }

	exibir(mat);
	cout << endl;

  return 1;
}


void mult(double a[][ordem], double b[][ordem]){
  double r[ordem][ordem];
	double soma=0,cont=0;
	int la=0,ca=0,lb=0,cb=0;
  while(la<ordem){
		if(lb==ordem && ca==ordem){
			r[la][cb]=soma;
			soma=0;
			cb++;lb=0;
			ca=0;
			cont++;
		}
		if(cont==ordem){
			ca=0;la++;
			lb=0;cb=0;
			cont=0;
		}
		soma += a[la][ca] * b[lb][cb];
		ca++; lb++;
	}
  exibir(r);
}




int main(){

    int pidpai;
    int fd[2];
    char line[buf];

     pipe(fd);
 
    cout<<"Entre com os valores de a"<< endl;
    preencher(matA);

    cout<<"Entre com os valores de b"<< endl;
    preencher(matB);
    pidpai = fork();
    if(pidpai == 0){  
			cout << "MATRIZ B INVERTIDA: " << endl;       
			inversa(matB,ordem);        
			close(fd[0]);
			for(int linha = 0 ; linha < ordem; linha++){
				for(int coluna = 0 ; coluna < ordem; coluna++){
					sprintf(line,"%lf",matB[linha][coluna]);					
					write(fd[1],line,buf);
					cout << "PROCESSO FILHO ESCREVE: " << line << endl;
				}
			}  
			cout << endl;
		}
  else{
    close(fd[1]);
		cout << "MATRIZ A INVERTIDA: " << endl;
    inversa(matA,ordem);
		for(int linha = 0 ; linha < ordem; linha++){
			for(int coluna = 0 ; coluna < ordem; coluna++){					
				read(fd[0],line,buf);		
				sscanf(line,"%lf", &matB[linha][coluna]);			
				cout << "PROCESSO PAI LE: " << line << endl;
			}
		}
		cout << endl;
		mult(matA,matB);
	}
    
    return 0;
}
