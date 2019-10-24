void agregar(int arr[], int n, int& len, int v){
    if(len == n){
        cout << "Está lleno" << endl;
    } else {
        arr[len] = v;
        len++;
    }

    return;
}

void inicializarVector(int arr[], int n){
    for(int i=0; i < n; i++){
        arr[i]=0;
    }

    return;
}

void mostrar(int arr[], int len){
    for(int i=0; i < len; i++){
        cout << "Posición: " << i << ". Valor " << arr[i] << endl;
    }

    return;
}

int buscar(int arr[], int len, int v){
    int i = 0;
    int pos;
    while(i < len && arr[i] != v){
        i++;
    }
    if(i == len){
        pos = -1;
    } else {
        pos = i;
    }

    return pos;
}

int buscar2(int arr[], int len, int v){
    int pos = -1;
    for(int i = 0; i < len; i++){
        if(arr[i] == v){
            pos = i;
            break;
        }
    }

    return pos;
}

void eliminar(int arr[],int& len, int pos){
    for(int i = pos; i < len - 1; i++){
        vec[i] = vec[i+1];
    }
    len--;
}

void insertar(int arr[], int &len, int v, int pos){
    for(int i = len-1; i >= pos; i--){
        arr[i+1] = arr[i];
    }
    arr[pos] = v;
    len++;
}

int insertarOrden(int arr[], int& len, int v){
    int i = 0;
    while (i < len && arr[i] <0 v){
        i++
    }
    insertar(arr, len, v, i);

    return i;
}

int buscaEinserta(int arr[], int& len, int v, bool enc){
    int pos = buscar(arr, len, v);
    if(pos != 1){
        enc = true;
    } else {
        enc = false;
        pos = insertarOrden(arr, len, v);
    }

    return pos;
}