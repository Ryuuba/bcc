/*Simulador de un sistema de "llamada bloqueada, llamada perdida" */

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

enum EvtTyp {arribo, muerte};
 
struct Evt {
	enum EvtTyp tipo;
	double t_evento;
	struct Evt *sig;
	};

double Tsim=0.0;     	//Tiempo de simulación (reloj)
struct Evt *head=NULL;   //Apunta siempre al primer evento de la LEF o a NULL si ésta está vacía


double uniforme(){
    const unsigned long long a=16807, m=2147483647;
    static unsigned long long seed = 1;
    seed=(a*seed)%m;
    return (double)seed/(double)m;
}
     
double expneg(double media){
	return -media*log(uniforme());       
}


double Erlang_B(unsigned int s,double a){//s: servidores, a: tráfico ofrecido
	double IB=1.0;
	for (int j=1;j<=s;j++)	IB=1.0+j*IB/a;
    return (1.0/IB);
}


enum EvtTyp evento_actual(){
	struct Evt *p=head;                      //Apuntador auxiliar. Sirve para liberar la memoria del primer evento de la LEF
	enum EvtTyp evt_inminente=head->tipo;    //Evento a procesar en main.
	Tsim=head->t_evento;                     //Actualiza el tiempo de simulación.		           
    head=head->sig;                          //Ahora head apunta al siguiente evento de la LEF o a Null si la lista e quedó vacía
	free(p);                                 //Libera memoria cupada por el primer evento de la LEF        
	return evt_inminente;                    //regresa el tipo de evento que se procesará
}


void programa_evento(enum EvtTyp type, double epoch){
	struct Evt *p; //Apuntador auxiliar para ir recorriendo la LEF
	bool insertado=0;  // insertado=0 indica que aún no se ha insertado el nuevo evento en la LEF
   
    struct Evt *newevt=(struct Evt *) malloc(sizeof(struct Evt));//Asigna memoria para el evento nuevo
	newevt->tipo=type; newevt->t_evento=epoch; //Datos del evento a programar
	
	newevt->sig=head; //"newevt->sig" apunta a NULL si la LEF está vacía o al primer evento de la LEF
	while (insertado==0){
		if(newevt->sig==NULL || (newevt->t_evento < (newevt->sig)->t_evento) ){
			if (newevt->sig==head) head=newevt; //nuevo se inserta al inicio de la LEF
			else p->sig=newevt;  //El evento nuevo se inserta entre dos eventos de la LEF o al final de la LEF
			insertado=1;      //Indica que ya se insertó el evento nuevo en la LEF
		}
		else {
			p=newevt->sig; //El apuntador auxiliar "p" apunta al evento al que actualmente apunta "nuevo->sig"
			newevt->sig=(newevt->sig)->sig; // ahora "nuevo->sig" apunta al siguiente evento de la lista			
		}
	}
	newevt=NULL;
}




int main(){
	std::cout<<"\nSimulador de un sistema BCC"<<std::endl;
	unsigned long arribos=0, bloqueados=0, N=1000000, j=0;//N=arribos a simular, j=estado del sistema	
	double mu=1/180.0;   	//Ts=1/mu: tiempo medio de servicio, en segundos/llamada
	int s=10; 				//Servidores
	double a=5;				//Tráfico ofrecido	
	
	//std::cout<<"\nNumero de arribos a simular: "<<std::endl;
	//std::cin>>N;	
	
	Tsim=0.0;
	programa_evento(arribo, Tsim); //Programa primer arribo en Tsim=0.0
	while(arribos < N){
    	if(evento_actual()==arribo){
	    	arribos++; 
			programa_evento(arribo, Tsim + expneg(1.0/(a*mu)));//lambda=a*mu;
	    	if(j<s)
		    {
		    	j++; 
		    	programa_evento(muerte, Tsim + expneg(1.0/mu));
		    }
	    	else bloqueados++;	
		}
		else {  //evento_actual==muerte
		    j--;
    	}	
    }//end while

	//Reporte de resultados
	double Pb=(float)bloqueados/arribos;   //Congestión en llamada (simulador)
	double Eb=Erlang_B(s,a);            //Congestión en tiempo analitico (Erlang B)

	std::cout<<"\n\n------------------ Resultados (Sistema BCC)----------------"<<std::endl;
	std::cout<<"\ns= "<<s<<", a="<<a<<std::endl;
	std::cout<<"\nCongestion en llamada (simulador), Pb    = "<<Pb*100.0<<" %"<<std::endl;
	std::cout<<"\nCongestion en tiempo  (analitico), B(s,a)= "<<100.0*Eb<<" %"<<std::endl;
	std::cout<<"\nTrafico cursado (analitico),  ac = "<<a*(1.0-Eb)<<" Erlangs"<<std::endl;
	std::cout<<"\n\n Tiempo simulado: " <<Tsim<<" segundos = "<<Tsim/3600<<" horas ="<<Tsim/(24*3600)<<" dias"<<std::endl;
	printf("\n\n-----------------------------------------------------------\n");

	system("pause");
	return 0;
}
