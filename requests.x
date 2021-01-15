
struct Posicion {
  int x;
  int y;
};

struct InfoAuto {
    Posicion posicion_pasajero;
    string tipo<>;
    string placa<>;
    int status;
};

struct Data {
    Posicion posicion_final;
    string placa<>;
};

program REQUESTS
{
    version SOLICITARVIAJEVERS1
    {
        InfoAuto SOLICITARVIAJE(Posicion) = 1;
        void TERMINARVIAJE(Data) = 2;
    } = 1;
} = 0x20000199;