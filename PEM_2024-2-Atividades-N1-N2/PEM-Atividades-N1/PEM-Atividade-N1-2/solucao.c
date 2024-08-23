#include <stdio.h>
#include <stdlib.h>

#define BATTERY_AMOUNT 5

const char *batteryLabels[BATTERY_AMOUNT] = {
    "Raciocínio Lógico",
    "Conceitos de Gerenciamento de Projetos",
    "Língua Inglesa",
    "Conceitos de Metodologia Ágil",
    "Linguagem Javascript"};

int requestRatesAmount();
float *requestRates(int);
void removeMinMaxRates(float *, int);
float evaluateCentralRate(float *, int);
void clearInputBuffer();

int main()
{
    // Notas centrais
    float centralRates[BATTERY_AMOUNT] = {0};

    int i;
    for (i = 0; i < BATTERY_AMOUNT; i++)
    {
        int ratesAmount = requestRatesAmount();

        if (ratesAmount <= 0)
            continue;

        float *rates = requestRates(ratesAmount);

        removeMinMaxRates(rates, ratesAmount);

        centralRates[i] = evaluateCentralRate(rates, ratesAmount);

        free(rates);
    }

    float finalRate = 0.0;
    for (i = 0; i < BATTERY_AMOUNT; i++)
    {
        printf("%s = %.2f\n", batteryLabels[i], centralRates[i]);
        finalRate += centralRates[i];
    }

    printf("Nota final do candidato = %.2f\n", finalRate);

    return 0;
}

int requestRatesAmount()
{
    int ratesAmount = 1;

    printf("Informe o número de notas: ");
    scanf("%d", &ratesAmount);

    while (ratesAmount == 1 || ratesAmount == 2)
    {
        clearInputBuffer();
        
        printf("O número de notas deve ser maior que 2.\n");
        printf("Informe o número de notas: ");
        scanf("%d", &ratesAmount);
    }

    clearInputBuffer();

    return ratesAmount;
}

float *requestRates(int ratesAmount)
{
    // Alocação dinâmica (pois o número de notas é desconhecido em tempo de compilação)
    float *rates = (float *)calloc(ratesAmount, sizeof(float));

    printf("Informe as notas: ");

    for (int i = 0; i < ratesAmount; i++)
        if (scanf("%f", &rates[i]) != 1)
            break;

    clearInputBuffer();

    return rates;
}

// Se o tamanho do vetor/quantidade de notas for menor que 2, ocorrerá comportamento indefinido
void removeMinMaxRates(float *rates, int ratesAmount)
{
    float minRate = rates[0];
    int minRateIndex = 0;
    float maxRate = -1.0; // Esse valor garante que não terão o mesmo indexador desde o início
    int maxRateIndex = -1;

    int i;
    for (i = 0; i < ratesAmount; i++)
    {
        if (rates[i] < minRate)
        {
            minRate = rates[i];
            minRateIndex = i;
        }
    }

    // Dois loops, para ser uma iteração que ignora o o indexador da menor nota
    // Isso garante que não adquirir o mesmo indexador
    for (i = 0; i < minRateIndex; i++)
    {
        if (rates[i] > maxRate)
        {
            maxRate = rates[i];
            maxRateIndex = i;
        }
    }
    for (i = minRateIndex + 1; i < ratesAmount; i++)
    {
        if (rates[i] > maxRate)
        {
            maxRate = rates[i];
            maxRateIndex = i;
        }
    }

    // Comportamento indefinido pode ocorrer aqui
    rates[minRateIndex] = 0.0;
    rates[maxRateIndex] = 0.0;
}

float evaluateCentralRate(float *rates, int ratesAmount)
{
    float sum = 0;
    for (int i = 0; i < ratesAmount; i++)
    {
        sum += rates[i];
    }

    return sum;
}

// Limpeza do buffer global de entradas (para impedir que o excesso interfirá no próximo scanf)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}