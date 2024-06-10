#include "libreria.h"

//Funcion para emitir por pantalla el archivo corredores_v1.csv
void listarTxt(FILE * aCsv)
{
    int i;
    char linea[500],delim[] = ";"; //Se crean el array linea y el array delim(que contiene ; porque es el caracter que separa los datos en el .csv(comma separated values)), necesarios para la funcion strtok
    struct competidor aux; //En el struct auxiliar se almacenan los datos de cada competidor para emitirlos.
    //char * token;
    aCsv=fopen("corredores_v1.csv","r+");
    if(aCsv!=NULL)
    {
        printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo\n",161,164,161);
        for(i=0; i<28; i++)                                                                           //Como inicialmente son 28 participantes y el txt no se modificará se establece la condicion directamente, sin variables.
        {
            fgets(linea,500,aCsv);                     //fgets obtiene la primera linea del archivo, luego esta linea es partida en "tokens" cada vez que se encuentra un ;
            aux.orden=atoi(strtok(linea,delim));       //Los datos enteros son convertidos con la función atoi
            aux.participante=atoi(strtok(NULL,delim));
            aux.dia=atoi(strtok(NULL,delim));
            strcpy(aux.mes,strtok(NULL,delim));        //Las cadenas son copiadas al struct con la función strcpy
            aux.anio=atoi(strtok(NULL,delim));
            aux.edad=atoi(strtok(NULL,delim));
            strcpy(aux.pais,strtok(NULL,delim));
            aux.tiempo=atof(strtok(NULL,delim));       //Tiempo, que es una variable float se convierte con la función atof
            printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\n\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo);
        }
        printf("\n");
        fclose(aCsv);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}

//Función auxiliar para emitir el menú principal y que el main este menos "poblado"
int menu()
{
    int opcion;
    printf("\t\t\t   Base de datos de participantes - Competencia de atletismo\n\n");
    printf("Seleccione la operaci%cn que desea realizar:\n\n",162);
    printf("1 - Listar por pantalla el registro de competidores inicial.\n\n");
    printf("2 - Crear un archivo binario para realizar modificaciones al registro.\n\n");
    printf("3 - Migrar los datos del archivo original al nuevo archivo binario.\n\n");
    printf("4 - Listar el archivo binario por pantalla.\n\n");
    printf("5 - Registrar un nuevo competidor.\n\n");
    printf("6 - Buscar los datos de un competidor.\n\n");
    printf("7 - Realizar la baja l%cgica de un competidor registrado.\n\n",162);
    printf("8 - Realizar la baja f%csica de los competidores que ha dado de baja, creando un nuevo archivo para almacenarlo.\n\n",161);
    printf("9- Listar el archivo que contiene los competidores dados de baja.\n\n");
    printf("0 - Cerrar el programa.\n");
    scanf(" %d",&opcion);
    fflush(stdin);
    while(opcion<0 || opcion>10)  //Se valida que el dato ingresado este dentro del rango de las opciones
    {
        printf("Ingrese un valor correspondiente a una opci%cn del programa:",162);
        scanf(" %d",&opcion);
        fflush(stdin);
    }
    printf("\n");
    return opcion;               //La función devuelve un entero, con el que se accede a las distintas opciones del switch
}

//Función para generar el archivo binario inicial
void crearBin(FILE * aBin)
{
    aBin=fopen("corredores.dat","wb"); //El modo wb crea el archivo
    if(aBin!=NULL)
    {
        printf("Archivo creado exitosamente.\n\n");
        fclose(aBin);
    }
    else
    {
        printf("Error al crear el archivo.\n\n");
    }
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}

//Función para migrar los datos del archivo .csv inicial al .dat creado con la función crearBin
void migrarDatos(FILE * aBin, FILE * aCsv)
{
    int i;
    struct competidor aux;
    aBin = fopen("corredores.dat","a+b");
    aCsv = fopen("corredores_v1.csv","r");

    if(aBin!=NULL && aCsv!=NULL)
    {
        fseek(aBin,0,SEEK_SET); //Se posiciona el cursor en la primera posición del archivo
        for(i=0; i<28; i++)
        {
            fscanf(aCsv,"%d;%d;%d;%3s;%d;%d;%3s;%f;",&aux.orden,&aux.participante,&aux.dia,aux.mes,&aux.anio,&aux.edad,aux.pais,&aux.tiempo); //Se leen los datos del csv y se almacenan en el registro.
            aux.activo=1;   //Con esta declaración se añade al registro el campo activo, que puede ser 1=activo o 0=inactivo
            fflush(stdin);
            fwrite(&aux,sizeof(struct competidor),1,aBin); //Se transfieren los datos del registro al archivo binario.
        }
        fclose(aBin);
        fclose(aCsv);
        printf("Migraci%cn de datos exitosa.\n",162);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}

//Función auxiliar para emitir el menú en la función listarDat y que su desarrollo este menos "poblado"
int menuListar()
{
    int opcion;
    printf("Seleccione el modo de listado del archivo binario:\n");
    printf("1 - Listar todos los campos, activos e inactivos.\n");
    printf("2 - Listar %cnicamente los campos activos.\n",163);
    printf("3 - Ingresar un pa%cs y mostrar todos los competidores de dicha nacionalidad.\n",161);
    printf("4 - Ingresar un rango de tiempos y mostrar todos los competidores cuyo tiempo entra en dicho rango.\n");
    scanf(" %d",&opcion);
    fflush(stdin);
    while(opcion<1 || opcion>4) //Se valida que el dato ingresado este dentro del rango de las opciones
    {
        printf("Ingrese un valor correspondiente a una opci%cn de la funci%cn",162,162);
        scanf(" %d",&opcion);
        fflush(stdin);
    }
    return opcion;  //La función devuelve un entero, con el que se accede a las distintas opciones del switch
}

//Función para emitir por pantalla el archivo binario previamente creado y al cual se han migrado los datos de corredores_v1.csv
void listarDat(FILE * aBin)
{
    int opcion;                         //Variable necesaria para el switch
    struct competidor aux;
    float margenInferior,margenSuperior; //Variables para delimitar el rango de tiempo si se elige la opción 4
    char pais[4],paisCompleto[30];       //Variables auxiliares para "cortar" el pais ingresado a una cadena de 3 caracteres, como las presentes en el archivo.
    aBin = fopen("corredores.dat","rb");
    if(aBin!=NULL)
    {
        fseek(aBin,0,SEEK_SET);
        opcion = menuListar();
        switch(opcion)
        {
        case 1:
            printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
            fread(&aux,sizeof(struct competidor),1,aBin); //Se realiza una leectura preventiva para que el último valor no se emita dos veces.
            while(!feof(aBin))
            {
                printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
                fread(&aux,sizeof(struct competidor),1,aBin);
            }
            fclose(aBin);
            break;
        case 2:
            printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
            fread(&aux,sizeof(struct competidor),1,aBin); //Se realiza una leectura preventiva para que el último valor no se emita dos veces.
            while(!feof(aBin))
            {
                if(aux.activo==1) //Se comprueba que el competidor que se emitirá por pantalla efectivamente esté activo y no haya sido dado de baja.
                {
                     printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
                }
                fread(&aux,sizeof(struct competidor),1,aBin);
            }
            fclose(aBin);
            break;
        case 3:
            printf("Ingrese el pa%cs por el cual desea filtrar los resultados: ",161);
            scanf(" %s",paisCompleto);
            fflush(stdin);
            strupr(paisCompleto); //Se mayusculiza la cadena ingresada
            strncpy(pais,paisCompleto,3); //Con esta función se establece la variable destino, la variable origen y la cantidad de caracteres que se copiaran de una a la otra.
            printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
            fread(&aux,sizeof(struct competidor),1,aBin); //Se realiza una leectura preventiva para que el último valor no se emita dos veces.
            while(!feof(aBin))
            {
                if(strcmp(pais,aux.pais)==0) //Si strcmp devuelve 0 es porque las cadenas son iguales, por lo tanto emite a los competidores del país elegido.
                {
                    printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
                }
                fread(&aux,sizeof(struct competidor),1,aBin);
            }
            fclose(aBin);
            break;
        case 4:
            printf("Ingrese el tiempo m%cnimo por el cual desea filtrar los resultados:\n",161);
            scanf(" %f",&margenInferior);
            fflush(stdin);
            printf("Ingrese el tiempo m%cximo por el cual desea filtrar los resultados:\n",160);
            scanf(" %f",&margenSuperior);                                                        //Se establecen los limites de tiempo entre los que debe buscar la función para emitir las coincidencias
            fflush(stdin);
            printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
            fread(&aux,sizeof(struct competidor),1,aBin); //Se realiza una leectura preventiva para que el último valor no se emita dos veces.
            while(!feof(aBin))
            {
                if(aux.tiempo>=margenInferior && aux.tiempo<=margenSuperior) //Se verifica que el campo .tiempo este dentro de los valores ingresados
                {
                    printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
                }
                fread(&aux,sizeof(struct competidor),1,aBin);
            }
            fclose(aBin);
            break;
        }
    }
    else
    {
        printf("Error al abrir el archivo.");
    }
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}

//Función para dar de alta a nuevos competidores, ingresando campo por campo los datos correspondientes.
void altaCompetidor(FILE * aBin)
{
    int ord;
    char paisCompleto[15],mesCompleto[15];
    struct competidor aux;
    aBin=fopen("corredores.dat","ab+");
    if(aBin!=NULL)
    {
        printf("Ingrese la posici%cn en la que desea introducir un nuevo corredor:",162);
        scanf(" %d",&ord);
        fflush(stdin);
        while(ord<0)
        {
            printf("Debe ingresar un n%cmero positivo. Por favor, ingrese una nueva posici%cn",163,162); //Se valida que ord sea positivo
            scanf(" %d",&ord);
            fflush(stdin);
        }

        fseek(aBin,((ord-1)*sizeof(struct competidor)),SEEK_SET); //Se posiciona el cursor del archivo binario en el espacio correspondiente a la variable ord
        fread(&aux,sizeof(struct competidor),1,aBin);             //y se lee el registro en esa posición, si el orden coincide con la variable se pedirá un nuevo ingreso ya que esto implica que el espacio está ocupado.
        fflush(stdin);
        while(ord==aux.orden)
        {
            printf("La posici%cn que desea llenar ya est%c ocupada. Por favor, ingrese otra posici%cn:",162,160,162);
            scanf(" %d",&ord);
            fflush(stdin);
            fseek(aBin,((ord-1)*sizeof(struct competidor)),SEEK_SET);
            fread(&aux,sizeof(struct competidor),1,aBin);
        }

        aux.orden=ord;
        printf("Ingrese el id del corredor:");
        scanf(" %d",&aux.participante);
        fflush(stdin);
        printf("Ingrese la fecha en la que corri%c. D%ca y a%co con n%cmeros, el mes con car%ccteres\n",162,161,164,163,160);
        printf("D%ca:",161);
        scanf(" %d",&aux.dia);
        fflush(stdin);
        while(aux.dia>31)
        {
            printf("Ingrese un d%ca v%clido:",161,160);
            scanf(" %d",&aux.dia);
            fflush(stdin);
        }
        printf("Mes:");
        scanf(" %s",mesCompleto);        //Se ingresa el mes completo a una variable
        fflush(stdin);
        strlwr(mesCompleto);            //luego se minusculiza
        strncpy(aux.mes,mesCompleto,3); //y se copian los primeros tres caracteres al registro.
        if(((strcmp(aux.mes,"abr")==0)||(strcmp(aux.mes,"jun")==0)||(strcmp(aux.mes,"sep")==0)||(strcmp(aux.mes,"nov")==0))&&(aux.dia>30)) //Se verifica que coincida                                                                                                                                      // cantidad de días en dicho mes
        {                                                                                                                                  //el mes ingresado con la
            printf("Ingrese un d%ca v%clido para el mes ingresado:\n",161,160);                                                            //cantidad de días en dicho mes.
            scanf(" %d",&aux.dia);
        }
        else if((strcmp(aux.mes,"feb")==0)&&(aux.dia>28))
        {
            printf("Ingrese un d%ca v%clido para el mes ingresado:\n",161,160);
            scanf(" %d",&aux.dia);
        }

        printf("A%co:",164);
        scanf(" %d",&aux.anio);
        if(aux.anio<2015)
        {
            printf("Ingrese un a%co v%clido, desde 2015:",164,160);            //Se verifica que el año ingresado este dentro del rango de la competición
            scanf(" %d",&aux.anio);
        }

        printf("Ingrese la edad del corredor:");
        scanf(" %d",&aux.edad);
        printf("Ingrese el pa%cs de origen del corredor:",161);
        scanf(" %s",paisCompleto);                                   //Se almacena el país completo a una variable,
        strupr(paisCompleto);                                        //luego se mayusculiza
        strncpy(aux.pais,paisCompleto,3);                            //y se almacenan los primeros tres caracteres en el registro.
        printf("Ingrese el tiempo del corredor:");
        scanf(" %f",&aux.tiempo);
        aux.activo=1;

        fseek(aBin,(aux.orden-1)*sizeof(struct competidor),SEEK_SET); //Se posiciona el cursor en la posición del orden ingresado.
        fwrite(&aux,sizeof(struct competidor),1,aBin);                //Se escribe el dato.

        fclose(aBin);
    }
    else
    {
        printf("Error al abrir el archivo.");
    }
}


void buscarCompetidor(FILE * aBin)
{
    int ord,id,opc,finReg;  //Se declaran variables para el orden
    int acierto=0;
    int i=0;
    struct competidor aux;
    aBin=fopen("corredores.dat","rb");
    if(aBin!=NULL)
    {
        fseek(aBin,0,SEEK_END);
        finReg=(ftell(aBin)/sizeof(struct competidor)); //Se calcula el total de registros y se almacena en una variable.
        fseek(aBin,0,SEEK_SET);
        printf("-0 Busqueda por orden\n-1 Busqueda por corredor\n");
        do
        {
            scanf(" %d",&opc);
            fflush(stdin);
        }
        while(opc!=0 && opc!=1);
        if(opc==0)
        {
            printf("Ingrese el orden del competidor que desea buscar:");
            scanf(" %d",&ord);
            fflush(stdin);
            fread(&aux,sizeof(struct competidor),1,aBin);
            for(i=0; i<finReg; i++)
            {
                if(aux.orden == ord)
                {
                    printf("Corredor|D%ca|   Mes   | A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
                    printf(" %d\t %d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
                    acierto=1;
                }
                fread(&aux,sizeof(struct competidor),1,aBin);
            }
            if(acierto==0)
            {
                printf("No se hall%c un competidor con ese n%cmero de orden.\n\n",162,163);
            }
            fclose(aBin);
        }
        if(opc==1)
        {
            printf("Ingrese el ID del competidor que desea buscar:");
            scanf(" %d",&id);
            fflush(stdin);
            fread(&aux,sizeof(struct competidor),1,aBin);
            for(i=0;i<finReg;i++)
            {
                if(aux.participante == id)
                {
                    printf("Orden| D%ca |    Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
                    printf(" %d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",aux.orden,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
                    acierto=1;
                }
                fread(&aux,sizeof(struct competidor),1,aBin);
            }
            if (acierto==0)
            {
                printf("No se hall%c un competidor con ese ID.\n\n",162);
            }
        }
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}


//Función para realizar la baja lógica de un competidor, que implica transformar su campo .activo de 1 a 0
void bajaLogica(FILE * aBin)
{
    int ord,conf; //Se definen variables para buscar el .orden del competidor y una para poder confirmar que se desea dar de baja al competidor.
    struct competidor aux;
    aBin=fopen("corredores.dat","rb+");
    if(aBin!=NULL)
    {
        printf("Ingrese el orden del competidor que desea dar de baja:\n");
        scanf(" %d",&ord);
        fflush(stdin);
        fseek(aBin,(ord-1)*sizeof(struct competidor),SEEK_SET); //Con el número de orden ya definido, se posiciona el cursor que recorre al archivo binario en la posición correcta para extraer los datos del competidor
        fread(&aux,sizeof(struct competidor),1,aBin); //Se extraen dichos datos
        printf("Dar%c de baja a: \n",160);
        printf("Orden|Corredor|D%ca|     Mes    | A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
        printf(" %d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
        printf("Est%c seguro que desea dar de baja al corredor %d?\nIngrese 1 para confirmar:\n",160,aux.orden);
        scanf(" %d",&conf); //Se pide el valor de confirmación
        fflush(stdin);
        if(conf==1)
        {
            aux.activo=0;
            fseek(aBin,(ord-1)*sizeof(struct competidor),SEEK_SET); //Dado que la función fread mueve un sizeof(variable ingresada) el cursor del archivo tras ser llamada, se vuelve a mover al cursor a la posición del orden ingresado
            fwrite(&aux,sizeof(struct competidor),1,aBin);
        }
        fseek(aBin,0,SEEK_SET); //Se vuelve a mover el cursor al primer lugar
        printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
        fread(&aux,sizeof(struct competidor),1,aBin);
        while(!feof(aBin))
        {
            if(aux.activo==1) //Para realizar la emisión de todos los competidores cuyo campo .activo es 1
            {
                printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
            }
            fread(&aux,sizeof(struct competidor),1,aBin);
        }
        fclose(aBin);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}

//Función para crear el archivo .xyz en el cual se almacenarán los competidores que han sido dados de baja utilizando la función bajaLogica
void bajaFisica(FILE * aBin,FILE * XYZ,char * nomArch)
{
    struct competidor aux;
    aBin=fopen("corredores.dat","rb+");
    XYZ = fopen(nomArch,"wb+");

    if(XYZ!=NULL)
    {
        fseek(aBin,0,SEEK_SET);
        fseek(XYZ,0,SEEK_SET); //Se establecen ambos cursores de los archivos binarios al principio del archivo
        fread(&aux,sizeof(struct competidor),1,aBin);
        while(!feof(aBin))      //Se realiza la lectura secuencial del archivo binario de competidores
        {
            if(aux.activo==0)       //Al encontrar una entrada con el campo activo=0
            {
                fwrite(&aux,sizeof(struct competidor),1,XYZ);   //Este es almacenado en el archivo .xyz
            }
            fread(&aux,sizeof(struct competidor),1,aBin);
        }

        fclose(aBin);
        fclose(XYZ);
    }
    else
    {
        printf("Error al abrir los archivos.\n");
    }
    printf("La migraci%cn de datos al nuevo archivo binario, %s ha sido exitosa.\n\n",162,nomArch);
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}

//Función para emitir por pantalla el archivo .xyz en el que se almacenan los competidores dados de baja
void listarXYZ(FILE * XYZ,char * nomArch)
{
    XYZ=fopen(nomArch,"rb+");
    struct competidor aux;
    if(XYZ!=NULL)
    {
        fseek(XYZ,0,SEEK_SET);
        printf("Orden|Corredor| D%ca |   Mes   |  A%co | Edad |   Pa%cs   |   Tiempo  | Activo\n",161,164,161);
        fread(&aux,sizeof(struct competidor),1,XYZ);
        while(!feof(XYZ))
        {
            printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",aux.orden,aux.participante,aux.dia,aux.mes,aux.anio,aux.edad,aux.pais,aux.tiempo,aux.activo);
            fread(&aux,sizeof(struct competidor),1,XYZ);
        }
        fclose(XYZ);
    }
    else
    {
        printf("Error al abrir el archivo.");
    }
    printf("\n");
    printf("Para continuar utilizando el programa, presione enter.\n");
    return;
}
