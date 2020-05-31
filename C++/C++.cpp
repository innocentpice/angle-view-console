// C++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

using namespace std;

int main()
{
    //Auto-Explicativo
    DWORD procId = GetProcId(L"ProjectG.exe");

    //Auto-Explicativo
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ProjectG.exe");

    //Pegando o processo
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    
    //Endereço base para o point trabalhar.
    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x007229D8;

    //Calculo para o point.
    std::vector<unsigned int> ammoOffsets = {0x8, 0xC, 0x28, 0x30, 0x0, 0x1DC, 0x68};
    uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

    float distancia = 0;
    float aux = 0;
    float angulo = 0;

    /*Estrutura de repetição basicamente o seguinte salvo o valor da distancia em um auxiliar e obtenho um novo
    valor da distancia e comparo novamente com a distancia sempre que forem diferentes ele refaz o calculo
    Obs: fiz assim pq estava com outra ideia mas desistio no meio do caminho*/
    ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &aux, sizeof(aux), nullptr);
    do
    {
        ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &distancia, sizeof(distancia), nullptr);
        if (distancia != aux)
        {
            if (distancia > 0)
            {
                angulo = asin(distancia) * 180 / 3.14;
                std::cout << "Angulo: = " << std::dec << angulo << std::endl;

            }
            else
            {
                angulo = asin(distancia) * 180 / 3.14;
                angulo = angulo * -1;
                std::cout << "Angulo: = " << std::dec << angulo << std::endl;
            }
            aux = distancia;
        }
    } while (true);
}