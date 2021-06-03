﻿#include "rodkinada.h"

/**
 * Введение в дисциплину
 */
void rodkinada::lab1()
{
  cout << "Hello, world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void rodkinada::lab2()
{
    for (int i = 0; i < N; i++) {
        int max = 0;
        for (int j = 0; j < N; j++){
            if (abs(A[max][i])<abs(A[j][i])) max = j;
        }
        swap(A[i], A[max]);
        swap(b[i], b[max]);
        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++){
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
            A[j][i] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        double d = A[i][i];
        for(int j = 0; j < N; j++){
            A[i][j]/= d;
        }
        b[i]/=d;
    }
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) x[i] -= A[i][j] * x[j];
    }
}



/**
 * Метод прогонки
 */
void rodkinada::lab3()
{
    double alpha[N - 1], beta[N];
    alpha[0] = - A[0][1] / A[0][0];
    beta[0] = b[0] / A[0][0];
    for (int i = 1; i < N; i++)
    {
        double y = A[i][i] + A[i][i - 1] * alpha[i - 1];
        alpha[i] = - A[i][i + 1] / y;
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / y;
    }
    x[N - 1] = beta[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }
}



/**
 * Метод Холецкого
 */
void rodkinada::lab4()
{
    double** S = new double* [N];
    double* D = new double[N];
    for (int i = 0; i < N; i++) S[i] = new double[N];

    for (int i = 0; i < N; i++) {
        double s = 0;
        for (int k = 0; k < i; k++) s += S[k][i] * S[k][i] * D[k];
        D[i] = (A[i][i] - s < 0 ? -1 : 1);
        S[i][i] = sqrt(abs(A[i][i] - s));

        for (int j = i + 1; j < N; j++) {
            s = 0;
            for (int k = 0; k < j; k++) s += S[k][i] * S[k][j] * D[k];
            S[i][j] = (A[i][j] - s) / (S[i][i] * D[i]);
        }
    }


    double* y = new double[N];
    for (int i = 0; i < N; i++) {
        double s = 0;
        for (int k = 0; k < i; k++) s += S[k][i] * D[k] * y[k];
        y[i] = (b[i] - s) / (S[i][i] * D[i]);
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++) y[i] -= S[i][k] * x[k];
        x[i] = y[i] / S[i][i];
    }
}



/**
 * Метод Якоби или Зейделя
 */
void rodkinada::lab5()
{
    double eps = 1e-10;
    double n = 1;
    double* tX = new double[N];
    for (int i = 0; i < N;i++) x[i] = 0;
    while (n>eps)
    {
        n = 0;
        for (int i = 0; i < N;i++) {
            tX[i] = b[i];
            for (int j = 0; j < N;j++) if (j != i) tX[i] -= A[i][j] * x[j];
            tX[i] /= A[i][i];
            n += fabs(tX[i] - x[i]);
            x[i] = tX[i];
        }
    }
    delete[]tX;
}



/**
 * Метод минимальных невязок
 */
void rodkinada::lab6()
{
    double *r = new double[N];
    double *Ar = new double[N];
    double eps = 1.e-9;

    bool flag = true;
    while (flag) {
        flag = false;

        for (int i = 0; i < N; i++) {
            r[i] = b[i];
            for (int j = 0; j < N; j++) {
                r[i] -= A[i][j] * x[j];
            }
        }

        for (int i = 0; i < N; i++) {
            Ar[i] = 0;
            for (int j = 0; j < N; j++) {
                Ar[i] += A[i][j] * r[j];
            }
        }

        double t = 0;
        double Ar_scalar = 0;
        for (int i = 0; i < N; i++) {
            t += Ar[i] * r[i];
            Ar_scalar += Ar[i] * Ar[i];
        }

        t /= Ar_scalar;
        for (int i = 0; i < N; i++) {
            double temp_x = x[i];
            x[i] = x[i] + t * r[i];
            if (fabs(x[i] - temp_x) > eps) {
                flag = true;
            }
        }
    }
    delete[] r;
    delete[] Ar;
}



/**
 * Метод сопряженных градиентов
 */
void rodkinada::lab7()
{

}


void rodkinada::lab8()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            if(A[i][j] != A[j][i]) return;
    }
    double **B = new double *[N];
    double t = 2;
    int maxi, maxj;
    for (int i = 0; i < N; i++) B[i] = new double[N];
    while (t > 1) {
        maxi = 0, maxj = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (fabs(A[i][j]) > fabs(A[maxi][maxj])) {
                    maxi = i;
                    maxj = j;
                }
            }
        }
        double phi = atan(2 * A[maxi][maxj] / (-A[maxi][maxi] + A[maxj][maxj])) / 2;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) B[i][j] = A[i][j];
        }
        for (int r = 0; r < N; r++) {
            B[r][maxi] = A[r][maxi] * cos(phi) - A[r][maxj] * sin(phi);
            B[r][maxj] = A[r][maxi] * sin(phi) + A[r][maxj] * cos(phi);
        }
        for (int c = 0; c < N; c++) {
            A[maxi][c] = B[maxi][c] * cos(phi) - B[maxj][c] * sin(phi);
            A[maxj][c] = B[maxi][c] * sin(phi) + B[maxj][c] * cos(phi);
        }
        A[maxi][maxj] = 0;
        t = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++)
                t += A[i][j] * A[i][j] + A[j][i] * A[j][i];
        }
    }
    for (int i = 0; i < N; i++) x[i] = A[i][i];
    for (int i = 0; i < N; i++) delete[] B[i];
    delete[] B;
}


void rodkinada::lab9()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (A[i][j] != A[j][i]) return;
    }
    double l, maxl = 0;
    bool cont = true;
    double *y = new double[N];
    double *y_prev = new double[N];
    for (int i = 0; i < N; i++) y_prev[i] = 1;
    while (cont) {
        cont = false;
        for (int i = 0; i < N; i++) {
            y[i] = 0;
            for (int j = 0; j < N; j++) {
                y[i] += A[i][j] * y_prev[j];
            }
        }
        l = 0;
        for (int i = 0; i < N; i++) {
            if (fabs(y[i]) > 1E-3 && fabs(y_prev[i]) > 1E-3) {
                l = y[i] / y_prev[i];
                break;
            }
        }
        if (fabs(l - maxl) > 1E-3) cont = true;
        maxl = l;
        for (int i = 0; i < N; i++) y_prev[i] = y[i];
    }
    cout << "The largest lambda: " << maxl << endl;
    delete[] y;
    delete[] y_prev;
}


std::string rodkinada::get_name()
{
  return "Rodkina D.A.";
}
