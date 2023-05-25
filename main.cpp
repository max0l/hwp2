#include <iostream>
#include <fstream>
#include <b15f/b15f.h>
#include <cmath>
#include <unistd.h>

#define STEPS 0.1
#define AE0 0
#define AE1 1
#define AE2 2
#define AE3 3
#define AE4 4
#define AE5 5

int main()
{
	std::ofstream output("test.txt");
	B15F& drv = B15F::getInstance();
	std::cout<< drv.analogRead(AE0) << "\n\n\n\n\n";
	drv.digitalWrite0(0);
	//Initial value of DAC if set to 1 = 0.007 mV after this its gets incrementet by 0,005 per step
	bool repeat = true;
	double u_read = 0;
	double u_write = 0;
    do
    {
    //std::cout<<std::hex<<drv.readDipSwitch()<<std::endl;
		//Diode Spannung
    	if(drv.readDipSwitch() == 1) {

			//Sets Voltage

			drv.analogWrite0(u_write*1023/5);
			std::cout<<"Sets Voltage to: " <<u_write<<std::endl;

			//Reads to voltage of acd
			u_read = drv.analogRead(0);
			std::cout<<u_read*5/1023<<std::endl;
			output <<  u_read*5/1023 << "\t" << u_write << std::endl;
			u_write+=STEPS;
			if(u_write > 5.0){
				break;
				u_write = 0.0;
			}
			drv.delay_ms(200);
	} else if(drv.readDipSwitch() == 2)
	//Diode Strom
		{
			drv.analogWrite0(u_write*1023/5);
			std::cout<<"Sets Voltage to: " <<u_write<<std::endl;


			u_read = drv.analogRead(0);
			double diode = (u_write-(u_read*5/1023));
			std::cout<<u_read*5/1023<<std::endl;
			output << diode << "\t" << u_write << std::endl;
			u_write+=0.1;
			if(u_write > 5.0){
				repeat = false;
				u_write = 0.0;
			}
			drv.delay_ms(200);
		}
		else if(drv.readDipSwitch() == 3)
		//Diode Strom über spannung gemessen
			{

				drv.analogWrite0(u_write*1023/5);
				std::cout<<"Sets Voltage to: " <<u_write<<std::endl;

				u_read = drv.analogRead(0);
				double diode = (u_write-(u_read*5/1023));
				std::cout<<u_read*5/1023 << "\t" << diode <<std::endl;
				output << diode << "\t" << (u_read*5/1023)/1000.0<< std::endl;

				u_write+=0.1;
				if(u_write > 5.0){
					u_write = 0.0;
					repeat = false;
				}
				drv.delay_ms(200);
			}

		else if(drv.readDipSwitch() == 4) {
			//8.4
			repeat = false;
			std::fstream fs;
			std::string outputFiles[7] = {"8.4-0vV.txt", "8.4-1vV.txt","8.4-2vV.txt","8.4-2.5vV.txt","8.4-3vV.txt","8.4-4vV.txt","8.4-5vV.txt"};
			double mainVoltages[7] = {0,1,2,2.5,3,4,5};

			for(int i = 0; i<=6; i++){
				fs.open(outputFiles[i], std::fstream::in | std::fstream::out | std::fstream::app);
				double main_voltage = mainVoltages[i];

				for(double voltage_step = 0.0; voltage_step<=5; voltage_step+=0.1) {

					//AA0
					drv.analogWrite0(voltage_step*1023/5);

					//AA1
					drv.analogWrite1(main_voltage*1023/5);
					std::cout<<"Sets Voltage to: " <<voltage_step<<std::endl;

					double resistor1 = 47.0;
					double resistor2 = 18000.0;
					//Reads to voltage of acd
					double u_ae0 = drv.analogRead(AE0)*(5.0/1023.0);
					double u_ae1 = drv.analogRead(AE1)*(5.0/1023.0);
					double u_ae2 = drv.analogRead(AE2)*(5.0/1023.0);
					double u_ae3 = drv.analogRead(AE3)*(5.0/1023.0);
					double u_gs = u_ae2;
					double u_sd = u_ae1;
					double i_drain = (u_ae0-u_ae1)/resistor1;
					double i_gate = u_gs/resistor2;



					std::cout <<"u_ae0: " << drv.analogRead(AE0) << "\t u_ae1: " << drv.analogRead(AE1) << "\t u_ae2: " << drv.analogRead(AE2) << "\t u_ae3: " << drv.analogRead(AE3) << std::endl;
					std::cout << "V: " << voltage_step << "\t u_ae0: " << u_ae0 << "\t u_ae1: " << u_ae1 << "\t u_ae2: " << u_ae2 << "\t u_ae3: " << u_ae3 << std::endl;

					std::cout<< "I drain: " <<i_drain << "\t" << "I Gate: " << i_gate <<std::endl;

					std::cout << "\n\n\n";
					//output << u_write << "\t" << u_read*5/1023<< std::endl;
					//output << u_write << "\t" << u_ae0 << "\t" << u_ae1 << "\t" << u_ae2 << "\t" << u_ae3 << std::endl;
					fs << i_drain << "\t" << u_sd <<std::endl;
					//drv.delay_ms(50);
				}
				fs.close();
			}
		}
		else if(drv.readDipSwitch() == 5) {
			//Strom spannung(8.6)
			repeat = false;
			std::fstream fs;
			std::string outputFiles[4] = {"8.6-2vV.txt", "8.6-3vV.txt","8.6-4vV.txt","8.6-5vV.txt"};
			double mainVoltages[4] = {2,3,4,5};

			for(int i = 0; i<=3; i++){
				std::cout << "Durchgang: " << i << std::endl;
				fs.open(outputFiles[i], std::fstream::in | std::fstream::out | std::fstream::app);
				double main_voltage = mainVoltages[i];

				for(double voltage_step = 0.0; voltage_step<=5; voltage_step+=0.1) {

					//AA1
					drv.analogWrite1(voltage_step*1023/5);

					//AA0
					drv.analogWrite0(main_voltage*1023/5);
					//std::cout<<"Sets Voltage to: " <<voltage_step<<std::endl;

					double resistor1 = 47.0;
					double resistor2 = 18000.0;
					//Reads to voltage of acd
					double u_ae0 = drv.analogRead(AE0)*(5.0/1023.0);
					double u_ae1 = drv.analogRead(AE1)*(5.0/1023.0);
					double u_ae2 = drv.analogRead(AE2)*(5.0/1023.0);
					double u_ae3 = drv.analogRead(AE3)*(5.0/1023.0);
					double u_gs = u_ae2;
					double u_sd = u_ae1;
					double i_drain = (u_ae0-u_ae1)/resistor1;
					double i_gate = u_gs/resistor2;



					//std::cout <<"u_ae0: " << drv.analogRead(AE0) << "\t u_ae1: " << drv.analogRead(AE1) << "\t u_ae2: " << drv.analogRead(AE2) << "\t u_ae3: " << drv.analogRead(AE3) << std::endl;
					//std::cout << "V: " << voltage_step << "\t u_ae0: " << u_ae0 << "\t u_ae1: " << u_ae1 << "\t u_ae2: " << u_ae2 << "\t u_ae3: " << u_ae3 << std::endl;

					//std::cout<< "I drain: " <<i_drain << "\t" << "I Gate: " << i_gate <<std::endl;

					//std::cout << "\n\n\n";
					//output << u_write << "\t" << u_read*5/1023<< std::endl;
					//output << u_write << "\t" << u_ae0 << "\t" << u_ae1 << "\t" << u_ae2 << "\t" << u_ae3 << std::endl;
					fs << i_drain << "\t" << u_gs <<std::endl;
					//drv.delay_ms(50);
				}
				fs.close();
			}
		}
		else if(drv.readDipSwitch() == 6) {
			//Strom strom(8.12)
			repeat = false;
			std::fstream fs;
			std::string outputFiles[4] = {"8.12-2vV.txt", "8.12-3vV.txt","8.12-4vV.txt","8.12-5vV.txt"};
			double mainVoltages[4] = {2,3,4,5};

			for(int i = 0; i<=3; i++){
				std::cout << "Durchgang: " << i << std::endl;
				fs.open(outputFiles[i], std::fstream::in | std::fstream::out | std::fstream::app);
				double main_voltage = mainVoltages[i];

				for(double voltage_step = 0.0; voltage_step<=5; voltage_step+=0.1) {

					//AA1
					drv.analogWrite1(voltage_step*1023/5);

					//AA0
					drv.analogWrite0(main_voltage*1023/5);
					drv.delay_ms(100);
					//std::cout<<"Sets Voltage to: " <<voltage_step<<std::endl;

					double resistor1 = 1000.0;
					double resistor2 = 18000.0;
					//Reads to voltage of acd
					double u_ae0 = drv.analogRead(AE0)*(5.0/1023.0);
					double u_ae1 = drv.analogRead(AE1)*(5.0/1023.0);
					double u_ae2 = drv.analogRead(AE2)*(5.0/1023.0);
					double u_ae3 = drv.analogRead(AE3)*(5.0/1023.0);
					double u_gs = u_ae2;
					double u_sd = u_ae1;
					double i_drain = (u_ae0-u_ae1)/resistor1;
					double i_gate = (u_ae2-u_ae3)/resistor2;



					//std::cout <<"u_ae0: " << drv.analogRead(AE0) << "\t u_ae1: " << drv.analogRead(AE1) << "\t u_ae2: " << drv.analogRead(AE2) << "\t u_ae3: " << drv.analogRead(AE3) << std::endl;
					//std::cout << "V: " << voltage_step << "\t u_ae0: " << u_ae0 << "\t u_ae1: " << u_ae1 << "\t u_ae2: " << u_ae2 << "\t u_ae3: " << u_ae3 << std::endl;

					//std::cout<< "I drain: " <<i_drain << "\t" << "I Gate: " << i_gate <<std::endl;

					//std::cout << "\n\n\n";
					//output << u_write << "\t" << u_read*5/1023<< std::endl;
					//output << u_write << "\t" << u_ae0 << "\t" << u_ae1 << "\t" << u_ae2 << "\t" << u_ae3 << std::endl;
					fs << i_drain << "\t" << i_gate <<std::endl;
					//drv.delay_ms(50);
				}
				fs.close();
			}
		}
		else if(drv.readDipSwitch() == 7) {
			//Strom spannung
			//8.11
			repeat = false;
			std::fstream fs;
			std::string outputFiles[7] = {"8.11-0vV.txt", "8.11-1vV.txt","8.11-2vV.txt", "8.11-2.5vV.txt" ,"8.11-3vV.txt","8.11-4vV.txt","8.11-5vV.txt"};
			double mainVoltages[7] = {0,1,2,2.5,3,4,5};

			for(int i = 0; i<=6; i++){
				std::cout << "Durchgang: " << i << std::endl;
				fs.open(outputFiles[i], std::fstream::in | std::fstream::out | std::fstream::app);
				double main_voltage = mainVoltages[i];

				for(double voltage_step = 0.0; voltage_step<=5; voltage_step+=0.1) {

					//AA0
					drv.analogWrite0(voltage_step*1023/5);

					//AA1
					drv.analogWrite1(main_voltage*1023/5);
					drv.delay_ms(200);
					//std::cout<<"Sets Voltage to: " <<voltage_step<<std::endl;

					double resistor1 = 47.0;
					double resistor2 = 18000.0;
					//Reads to voltage of acd
					double u_ae0 = drv.analogRead(AE0)*(5.0/1023.0);
					double u_ae1 = drv.analogRead(AE1)*(5.0/1023.0);
					double u_ae2 = drv.analogRead(AE2)*(5.0/1023.0);
					double u_ae3 = drv.analogRead(AE3)*(5.0/1023.0);
					double u_gs = u_ae2;
					double u_sd = u_ae1;
					double i_drain = (u_ae0-u_ae1)/resistor1;
					double i_gate = (u_ae3-u_ae2)/resistor2; //3-2/R2



					//std::cout <<"u_ae0: " << drv.analogRead(AE0) << "\t u_ae1: " << drv.analogRead(AE1) << "\t u_ae2: " << drv.analogRead(AE2) << "\t u_ae3: " << drv.analogRead(AE3) << std::endl;
					//std::cout << "V: " << voltage_step << "\t u_ae0: " << u_ae0 << "\t u_ae1: " << u_ae1 << "\t u_ae2: " << u_ae2 << "\t u_ae3: " << u_ae3 << std::endl;

					//std::cout<< "I drain: " <<i_drain << "\t" << "I Gate: " << i_gate <<std::endl;

					//std::cout << "\n\n\n";
					//output << u_write << "\t" << u_read*5/1023<< std::endl;
					//output << u_write << "\t" << u_ae0 << "\t" << u_ae1 << "\t" << u_ae2 << "\t" << u_ae3 << std::endl;
					fs << i_drain << "\t" << voltage_step <<std::endl;

					//drv.delay_ms(50);
				}
				fs.close();
			}
		}
		else if(drv.readDipSwitch() == 8){
			while(true){
				drv.analogWrite1(1023);
				drv.analogWrite1(0);
			}
		} else if(drv.readDipSwitch() == 16) {
			//repeat = true;
			//BSN10A
			drv.analogWrite0(1023);
			drv.analogWrite1(1023);

			drv.digitalWrite0(0);
			drv.digitalWrite1(0);
			int dgr0= drv.digitalRead0();
			int dgr1= drv.digitalRead1();
			std::cout<<"Ausgegeben: 00"<<std::endl;
			std::cout<<"Gelesen: "<<dgr1 << dgr0<<"\n\n"<<std::endl;
			getchar();
			drv.digitalWrite0(1);
			drv.digitalWrite1(0);
			dgr0= drv.digitalRead0();
			dgr1= drv.digitalRead1();
			std::cout<<"Ausgegeben: 01"<<std::endl;
			std::cout<<"Gelesen: "<<dgr1 << dgr0<<"\n\n"<<std::endl;
			getchar();
			drv.digitalWrite0(0);
			drv.digitalWrite1(1);
			dgr0= drv.digitalRead0();
			dgr1= drv.digitalRead1();
			std::cout<<"Ausgegeben: 10"<<std::endl;
			std::cout<<"Gelesen: "<<dgr1 << dgr0<<"\n\n"<<std::endl;
			getchar();
			drv.digitalWrite0(1);
			drv.digitalWrite1(1);
			dgr0= drv.digitalRead0();
			dgr1= drv.digitalRead1();
			std::cout<<"Ausgegeben: 11"<<std::endl;
			std::cout<<"Gelesen: "<<dgr1 << dgr0<<"\n\n"<<std::endl;
			getchar();

		}
	}while(repeat);
		drv.analogWrite0(0);
    output.close();

}
