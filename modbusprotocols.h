extern "C" {
#define MODBUSPROTOCOLS_H


int initialiseRTU(void);
int setRTUmode(void);
int settimeouts(void);
int RTU_connect(void);
int report_slave_ID(void);
int readaddresses(void);
int setmodbusslave(int);

int testfunction(void);
}
