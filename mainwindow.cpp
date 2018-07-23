#include "mainwindow.h"
#include "ui_mainwindow.h"
QLabel *status[12];
QLCDNumber *statusnum[12];
QLabel *table[10][13][13];
QLabel *monster[2][12];
QLabel *background;
QLCDNumber *monsternum[2][12];
QPushButton *NPCtext[5],*NPCchoice[5][4];
QLabel *thing[5][10],*thingx[5][10];
int isWall[10][13][13];
int Xposition[10],Yposition[10];
int i,j,k,l,Xkeycount=0,Zkeycount=0;
int longgang=0,yinggang=0;
int floornum,levelnum,HPnum,attacknum,defencenum,magicdefencenum,expnum;
int goldnum,yellowkeynum,bluekeynum,redkeynum,greenkeynum;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setGeometry(0,0,800,600);
    setWindowTitle("Magic Tower");
    setWindowIcon(QIcon(":title.ico"));
    background=new QLabel(" ",this);
    background->setGeometry(0,0,800,600);
    background->setStyleSheet("border-image: url(:/background.jpg);");
    background->show();
    for(i=0;i<5;i++){
        for(j=0;j<10;j++){
            thing[i][j]=new QLabel(" ",this);
            thingx[i][j]=new QLabel(" ",this);
            thing[i][j]->setGeometry(120*i,20+40*j,40,40);
            thingx[i][j]->setGeometry(40+120*i,20+40*j,80,40);
            thingx[i][j]->setStyleSheet("color:white;");
            thing[i][j]->hide();thingx[i][j]->hide();
        }
    }
    for(i=0;i<2;i++){
        for(j=0;j<12;j++){
            monster[i][j]=new QLabel(" ",this);
            monster[i][j]->setGeometry(240*i,20+40*j,40,40);
            monster[i][j]->hide();
            monsternum[i][j]=new QLCDNumber(1,this);
            monsternum[i][j]->setDigitCount(7);
            monsternum[i][j]->setStyleSheet("color:white;");
            monsternum[i][j]->setGeometry(240*i+40,20+40*j,160,40);
            monsternum[i][j]->hide();
        }
    }
    for(i=0;i<10;i++){
        for(j=0;j<13;j++){
            for(k=0;k<13;k++){
                table[i][j][k]=new QLabel(" ",this);
                table[i][j][k]->setGeometry(40*j,20+40*k,40,40);
                table[i][j][k]->hide();
            }
        }
    }
    for(l=0;l<12;l++){
        status[l]=new QLabel(" ",this);
        statusnum[l]=new QLCDNumber(1,this);
        status[l]->setGeometry(600,20+40*l,80,40);
        statusnum[l]->setGeometry(700,20+40*l,80,40);
        statusnum[l]->setDigitCount(5);
    }
    setstatus();
    settable1();
    settable2();
    settable3();
    settable4();
    settable5();
    settable6();
    settable7();
    settable8();
    settable9();
    settable10();
    setplayer();
    for(j=0;j<13;j++){
        for(k=0;k<13;k++){
            table[0][j][k]->show();
        }
    }
    for(i=0;i<5;i++){
        NPCtext[i]=new QPushButton(" ",this);
        NPCtext[i]->setGeometry(120,380,280,80);
        NPCtext[i]->hide();
        for(j=0;j<4;j++){
            NPCchoice[i][j]=new QPushButton(" ",this);
            NPCchoice[i][j]->setGeometry(120+j%2*140,460+j/2*40,140,40);
            NPCchoice[i][j]->hide();
        }
    }
    connect(NPCchoice[0][0],SIGNAL(clicked(bool)),this,SLOT(npcchoice00()));
    connect(NPCchoice[0][1],SIGNAL(clicked(bool)),this,SLOT(npcchoice01()));
    connect(NPCchoice[0][2],SIGNAL(clicked(bool)),this,SLOT(npcchoice02()));
    connect(NPCchoice[0][3],SIGNAL(clicked(bool)),this,SLOT(npcchoice03()));
    connect(NPCchoice[1][0],SIGNAL(clicked(bool)),this,SLOT(npcchoice10()));
    connect(NPCchoice[1][1],SIGNAL(clicked(bool)),this,SLOT(npcchoice11()));
    connect(NPCchoice[1][2],SIGNAL(clicked(bool)),this,SLOT(npcchoice12()));
    connect(NPCchoice[2][0],SIGNAL(clicked(bool)),this,SLOT(npcchoice20()));
    connect(NPCchoice[2][1],SIGNAL(clicked(bool)),this,SLOT(npcchoice21()));
    connect(NPCchoice[2][2],SIGNAL(clicked(bool)),this,SLOT(npcchoice22()));
    connect(NPCchoice[2][3],SIGNAL(clicked(bool)),this,SLOT(npcchoice23()));
    connect(NPCchoice[3][0],SIGNAL(clicked(bool)),this,SLOT(npcchoice30()));
    connect(NPCchoice[3][1],SIGNAL(clicked(bool)),this,SLOT(npcchoice31()));
    connect(NPCchoice[4][0],SIGNAL(clicked(bool)),this,SLOT(npcchoice40()));
    QSound::play("C:/QtProject/MagicTower/BGM.wav");
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_S){
        switch (isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]) {
        case -104:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
            NPCtext[3]->setText("30 gold, you can get:");NPCtext[3]->show();
            NPCchoice[3][0]->setText("5 magicdefence");NPCchoice[3][0]->show();
            NPCchoice[3][1]->setText("Exit");NPCchoice[3][1]->show();
            break;
        }
        case -103:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
            NPCtext[2]->setText("50 gold, you can get:");NPCtext[2]->show();
            NPCchoice[2][0]->setText("1 yellowkey");NPCchoice[2][0]->show();
            NPCchoice[2][1]->setText("1 bluekey");NPCchoice[2][1]->show();
            NPCchoice[2][2]->setText("1 redkey");NPCchoice[2][2]->show();
            NPCchoice[2][3]->setText("Exit");NPCchoice[2][3]->show();
            break;
        }
        case -102:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
            NPCtext[1]->setText("Welcome, you can get:");NPCtext[1]->show();
            NPCchoice[1][0]->setText("5 attack");NPCchoice[1][0]->show();
            NPCchoice[1][1]->setText("7 defence");NPCchoice[1][1]->show();
            NPCchoice[1][2]->setText("1000 HP");NPCchoice[1][2]->show();
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
            break;
        }
        case -101:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
            NPCtext[0]->setText("50 gold, you can get:");NPCtext[0]->show();
            NPCchoice[0][0]->setText("5 attack");NPCchoice[0][0]->show();
            NPCchoice[0][1]->setText("7 defence");NPCchoice[0][1]->show();
            NPCchoice[0][2]->setText("1000 HP");NPCchoice[0][2]->show();
            NPCchoice[0][3]->setText("Exit");NPCchoice[0][3]->show();
            break;
        }
        case -9:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;defencenum+=5;
            statusnum[4]->display(defencenum);break;
        }
        case -8:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;attacknum+=5;
            statusnum[3]->display(attacknum);break;
        }
        case -7:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;magicdefencenum+=10;
            statusnum[5]->display(magicdefencenum);break;
        }
        case -6:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;HPnum+=200;
            statusnum[2]->display(HPnum);break;
        }
        case -5:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;redkeynum++;
            statusnum[10]->display(redkeynum);break;
        }
        case -4:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;bluekeynum++;
            statusnum[9]->display(bluekeynum);break;
        }
        case -3:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;yellowkeynum++;
            statusnum[8]->display(yellowkeynum);break;
        }
        case -2:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
            NPCtext[4]->setText("Thank you for saving me!");NPCtext[4]->show();
            NPCchoice[4][0]->setText("Exit");NPCchoice[4][0]->show();
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
            break;
        }
        case -1:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;break;
        }
        case 0:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
            break;
        }
        case 1:{
            if(yellowkeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;yellowkeynum--;
                statusnum[8]->display(yellowkeynum);break;
            }else{
                break;
            }
        }
        case 2:{
            if(bluekeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;bluekeynum--;
                statusnum[9]->display(bluekeynum);break;
            }else{
                break;
            }
        }
        case 3:{
            if(redkeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;redkeynum--;
                statusnum[10]->display(redkeynum);break;
            }else{
                break;
            }
        }
        case 4:{
            if(greenkeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;greenkeynum--;
                statusnum[11]->display(greenkeynum);break;
            }else{
                break;
            }
        }
        case 5:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;attacknum++;
            statusnum[3]->display(attacknum);break;
        }
        case 6:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;defencenum++;
            statusnum[4]->display(defencenum);break;
        }
        case 7:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;HPnum+=500;
            statusnum[2]->display(HPnum);break;
        }
        case 8:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;HPnum+=1000;
            statusnum[2]->display(HPnum);break;
        }
        case 9:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;break;
        }
        case 10:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            break;
        }
        case 11:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            break;
        }
        case 12:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;HPnum-=100;
            statusnum[2]->display(HPnum);break;
        }
        case 13:{
            if(battle(attacknum,magicdefencenum,1000,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1000,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 14:{
            if(battle(attacknum,defencenum,100,15,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,100,15,0,1);statusnum[2]->display(HPnum);
                goldnum+=3;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 15:{
            if(battle(attacknum,defencenum,500,14,2,3)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,500,14,2,3);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 16:{
            if(battle(attacknum,magicdefencenum,200,20,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,200,20,0,1);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 17:{
            if(battle(attacknum,magicdefencenum,400,40,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,400,40,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 18:{
            if(battle(attacknum,defencenum,700,26,4,10)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,700,26,4,10);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 19:{
            if(battle(attacknum,defencenum,1000,108,0,99)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,1000,108,0,99);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 20:{
            if(battle(attacknum,defencenum,444,18,18,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,444,18,18,1);statusnum[2]->display(HPnum);
                goldnum+=4;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 21:{
            if(battle(attacknum,magicdefencenum,800,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 22:{
            if(battle(attacknum,magicdefencenum,120,30,60,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,120,30,60,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 23:{
            if(battle(attacknum,magicdefencenum,360,60,90,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,360,60,90,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 24:{
            if(battle(attacknum,magicdefencenum,800,80,120,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,120,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 25:{
            if(battle(attacknum,defencenum,555,15,20,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,555,15,20,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 26:{
            if(battle(attacknum,defencenum,777,30,40,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,777,30,40,1);statusnum[2]->display(HPnum);
                goldnum+=12;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 27:{
            if(battle(attacknum,defencenum,999,60,80,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,999,60,80,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 28:{
            if(battle(attacknum,magicdefencenum,1500,70,35,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,70,35,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 29:{
            if(battle(attacknum,magicdefencenum,3000,140,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,3000,140,0,1);statusnum[2]->display(HPnum);
                goldnum+=50;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 30:{
            if(battle(attacknum,magicdefencenum,888,88,88,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,888,88,88,1);statusnum[2]->display(HPnum);
                goldnum+=30;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 31:{
            if(yinggang){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;break;
            }
        }
        case 32:{
            if(longgang){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;break;
            }
        }
        case 33:{
            if(battle(attacknum,magicdefencenum,1500,200,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,200,0,1);statusnum[2]->display(HPnum);
                goldnum+=100;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 34:{
            if(battle(attacknum,defencenum,5000,500,200,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,5000,500,200,1);statusnum[2]->display(HPnum);
                goldnum+=200;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 35:{
            if(battle(attacknum,defencenum,3000,800,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,3000,800,0,1);statusnum[2]->display(HPnum);
                goldnum+=9999;expnum++;Yposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/player.png);");
                break;
            }
        }
        case 36:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;longgang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 37:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;yinggang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 38:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;attacknum+=20;
            statusnum[3]->display(attacknum);break;
        }
        case 39:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;defencenum+=20;
            statusnum[4]->display(defencenum);break;
        }
        case 101:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=9;table[3][2][9]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][3]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        case 102:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[9][j][k]->show();
                }
            }
            floornum=10;statusnum[0]->display(9999);
            break;
        }
        case 111:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=3;table[3][2][3]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][9]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        default:
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]->setStyleSheet("border-image: url(:/player.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]+1]=-1;Yposition[floornum-1]++;break;
        }
    }else if(e->key() == Qt::Key_A){
        switch (isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]) {
        case -104:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            NPCtext[3]->setText("30 gold, you can get:");NPCtext[3]->show();
            NPCchoice[3][0]->setText("5 magicdefence");NPCchoice[3][0]->show();
            NPCchoice[3][1]->setText("Exit");NPCchoice[3][1]->show();
            break;
        }
        case -103:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            NPCtext[2]->setText("50 gold, you can get:");NPCtext[2]->show();
            NPCchoice[2][0]->setText("1 yellowkey");NPCchoice[2][0]->show();
            NPCchoice[2][1]->setText("1 bluekey");NPCchoice[2][1]->show();
            NPCchoice[2][2]->setText("1 redkey");NPCchoice[2][2]->show();
            NPCchoice[2][3]->setText("Exit");NPCchoice[2][3]->show();
            break;
        }
        case -102:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            NPCtext[1]->setText("Welcome, you can get:");NPCtext[1]->show();
            NPCchoice[1][0]->setText("5 attack");NPCchoice[1][0]->show();
            NPCchoice[1][1]->setText("7 defence");NPCchoice[1][1]->show();
            NPCchoice[1][2]->setText("1000 HP");NPCchoice[1][2]->show();
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
            break;
        }
        case -101:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            NPCtext[0]->setText("50 gold, you can get:");NPCtext[0]->show();
            NPCchoice[0][0]->setText("5 attack");NPCchoice[0][0]->show();
            NPCchoice[0][1]->setText("7 defence");NPCchoice[0][1]->show();
            NPCchoice[0][2]->setText("1000 HP");NPCchoice[0][2]->show();
            NPCchoice[0][3]->setText("Exit");NPCchoice[0][3]->show();
            break;
        }
        case -9:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;defencenum+=5;
            statusnum[4]->display(defencenum);break;
        }
        case -8:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;attacknum+=5;
            statusnum[3]->display(attacknum);break;
        }
        case -7:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;magicdefencenum+=10;
            statusnum[5]->display(magicdefencenum);break;
        }
        case -6:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;HPnum+=200;
            statusnum[2]->display(HPnum);break;
        }
        case -5:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;redkeynum++;
            statusnum[10]->display(redkeynum);break;
        }
        case -4:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;bluekeynum++;
            statusnum[9]->display(bluekeynum);break;
        }
        case -3:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;yellowkeynum++;
            statusnum[8]->display(yellowkeynum);break;
        }
        case -2:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            NPCtext[4]->setText("Thank you for saving me!");NPCtext[4]->show();
            NPCchoice[4][0]->setText("Exit");NPCchoice[4][0]->show();
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
            break;
        }
        case -1:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;break;
        }
        case 0:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            break;
        }
        case 1:{
            if(yellowkeynum>0){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;yellowkeynum--;
                statusnum[8]->display(yellowkeynum);break;
            }else{
                break;
            }
        }
        case 2:{
            if(bluekeynum>0){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;bluekeynum--;
                statusnum[9]->display(bluekeynum);break;
            }else{
                break;
            }
        }
        case 3:{
            if(redkeynum>0){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;redkeynum--;
                statusnum[10]->display(redkeynum);break;
            }else{
                break;
            }
        }
        case 4:{
            if(greenkeynum>0){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;greenkeynum--;
                statusnum[11]->display(greenkeynum);break;
            }else{
                break;
            }
        }
        case 5:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;attacknum++;
            statusnum[3]->display(attacknum);break;
        }
        case 6:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;defencenum++;
            statusnum[4]->display(defencenum);break;
        }
        case 7:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;HPnum+=500;
            statusnum[2]->display(HPnum);break;
        }
        case 8:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;HPnum+=1000;
            statusnum[2]->display(HPnum);break;
        }
        case 9:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;break;
        }
        case 10:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            break;
        }
        case 11:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            break;
        }
        case 12:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;HPnum-=100;
            statusnum[2]->display(HPnum);break;
        }
        case 13:{
            if(battle(attacknum,magicdefencenum,1000,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1000,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 14:{
            if(battle(attacknum,defencenum,100,15,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,100,15,0,1);statusnum[2]->display(HPnum);
                goldnum+=3;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 15:{
            if(battle(attacknum,defencenum,500,14,2,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,500,14,2,1);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 16:{
            if(battle(attacknum,magicdefencenum,200,20,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,200,20,0,1);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 17:{
            if(battle(attacknum,magicdefencenum,400,40,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,400,40,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 18:{
            if(battle(attacknum,defencenum,700,26,4,10)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,700,26,4,10);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 19:{
            if(battle(attacknum,defencenum,1000,108,0,99)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,1000,108,0,99);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 20:{
            if(battle(attacknum,defencenum,444,18,18,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,444,18,18,1);statusnum[2]->display(HPnum);
                goldnum+=4;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 21:{
            if(battle(attacknum,magicdefencenum,800,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 22:{
            if(battle(attacknum,magicdefencenum,120,30,60,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,120,30,60,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 23:{
            if(battle(attacknum,magicdefencenum,360,60,90,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,360,60,90,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 24:{
            if(battle(attacknum,magicdefencenum,800,80,120,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,120,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 25:{
            if(battle(attacknum,defencenum,555,15,20,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,555,15,20,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 26:{
            if(battle(attacknum,defencenum,777,30,40,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,777,30,40,1);statusnum[2]->display(HPnum);
                goldnum+=12;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 27:{
            if(battle(attacknum,defencenum,999,60,80,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floorleft.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,999,60,80,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 28:{
            if(battle(attacknum,magicdefencenum,1500,70,35,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,70,35,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 29:{
            if(battle(attacknum,magicdefencenum,3000,140,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,3000,140,0,1);statusnum[2]->display(HPnum);
                goldnum+=50;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 30:{
            if(battle(attacknum,magicdefencenum,888,88,88,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,888,88,88,1);statusnum[2]->display(HPnum);
                goldnum+=30;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 31:{
            if(yinggang){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;break;
            }
        }
        case 32:{
            if(longgang){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;break;
            }
        }
        case 33:{
            if(battle(attacknum,magicdefencenum,1500,200,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,200,0,1);statusnum[2]->display(HPnum);
                goldnum+=100;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 34:{
            if(battle(attacknum,defencenum,5000,500,200,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,5000,500,200,1);statusnum[2]->display(HPnum);
                goldnum+=200;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 35:{
            if(battle(attacknum,defencenum,3000,800,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,3000,800,0,1);statusnum[2]->display(HPnum);
                goldnum+=9999;expnum++;Xposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
                break;
            }
        }
        case 36:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;longgang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 37:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;yinggang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 38:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;attacknum+=20;
            statusnum[3]->display(attacknum);break;
        }
        case 39:{
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;defencenum+=20;
            statusnum[4]->display(defencenum);break;
        }
        case 101:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=9;table[3][2][9]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][3]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        case 102:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[9][j][k]->show();
                }
            }
            floornum=10;statusnum[0]->display(9999);
            break;
        }
        case 111:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=3;table[3][2][3]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][9]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        default:
            table[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerleft.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]-1][Yposition[floornum-1]]=-1;Xposition[floornum-1]--;break;
        }
    }else if(e->key() == Qt::Key_D){
        switch (isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]) {
        case -104:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            NPCtext[3]->setText("30 gold, you can get:");NPCtext[3]->show();
            NPCchoice[3][0]->setText("5 magicdefence");NPCchoice[3][0]->show();
            NPCchoice[3][1]->setText("Exit");NPCchoice[3][1]->show();
            break;
        }
        case -103:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            NPCtext[2]->setText("50 gold, you can get:");NPCtext[2]->show();
            NPCchoice[2][0]->setText("1 yellowkey");NPCchoice[2][0]->show();
            NPCchoice[2][1]->setText("1 bluekey");NPCchoice[2][1]->show();
            NPCchoice[2][2]->setText("1 redkey");NPCchoice[2][2]->show();
            NPCchoice[2][3]->setText("Exit");NPCchoice[2][3]->show();
            break;
        }
        case -102:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            NPCtext[1]->setText("Welcome, you can get:");NPCtext[1]->show();
            NPCchoice[1][0]->setText("5 attack");NPCchoice[1][0]->show();
            NPCchoice[1][1]->setText("7 defence");NPCchoice[1][1]->show();
            NPCchoice[1][2]->setText("1000 HP");NPCchoice[1][2]->show();
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]+1]=-1;
            break;
        }
        case -101:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            NPCtext[0]->setText("50 gold, you can get:");NPCtext[0]->show();
            NPCchoice[0][0]->setText("5 attack");NPCchoice[0][0]->show();
            NPCchoice[0][1]->setText("7 defence");NPCchoice[0][1]->show();
            NPCchoice[0][2]->setText("1000 HP");NPCchoice[0][2]->show();
            NPCchoice[0][3]->setText("Exit");NPCchoice[0][3]->show();
            break;
        }
        case -9:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;defencenum+=5;
            statusnum[4]->display(defencenum);break;
        }
        case -8:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;attacknum+=5;
            statusnum[3]->display(attacknum);break;
        }
        case -7:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;magicdefencenum+=10;
            statusnum[5]->display(magicdefencenum);break;
        }
        case -6:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;HPnum+=200;
            statusnum[2]->display(HPnum);break;
        }
        case -5:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;redkeynum++;
            statusnum[10]->display(redkeynum);break;
        }
        case -4:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;bluekeynum++;
            statusnum[9]->display(bluekeynum);break;
        }
        case -3:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;yellowkeynum++;
            statusnum[8]->display(yellowkeynum);break;
        }
        case -2:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            NPCtext[4]->setText("Thank you for saving me!");NPCtext[4]->show();
            NPCchoice[4][0]->setText("Exit");NPCchoice[4][0]->show();
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
            break;
        }
        case -1:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;break;
        }
        case 0:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            break;
        }
        case 1:{
            if(yellowkeynum>0){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;yellowkeynum--;
                statusnum[8]->display(yellowkeynum);break;
            }else{
                break;
            }
        }
        case 2:{
            if(bluekeynum>0){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;bluekeynum--;
                statusnum[9]->display(bluekeynum);break;
            }else{
                break;
            }
        }
        case 3:{
            if(redkeynum>0){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;redkeynum--;
                statusnum[10]->display(redkeynum);break;
            }else{
                break;
            }
        }
        case 4:{
            if(greenkeynum>0){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;greenkeynum--;
                statusnum[11]->display(greenkeynum);break;
            }else{
                break;
            }
        }
        case 5:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;attacknum++;
            statusnum[3]->display(attacknum);break;
        }
        case 6:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;defencenum++;
            statusnum[4]->display(defencenum);break;
        }
        case 7:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;HPnum+=500;
            statusnum[2]->display(HPnum);break;
        }
        case 8:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;HPnum+=1000;
            statusnum[2]->display(HPnum);break;
        }
        case 9:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;break;
        }
        case 10:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            break;
        }
        case 11:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            break;
        }
        case 12:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;HPnum-=100;
            statusnum[2]->display(HPnum);break;
        }
        case 13:{
            if(battle(attacknum,magicdefencenum,1000,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1000,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 14:{
            if(battle(attacknum,defencenum,100,15,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,1000,15,0,1);statusnum[2]->display(HPnum);
                goldnum+=3;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 15:{
            if(battle(attacknum,defencenum,500,14,2,3)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,500,14,2,3);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 16:{
            if(battle(attacknum,magicdefencenum,200,20,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,200,20,0,1);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 17:{
            if(battle(attacknum,magicdefencenum,400,40,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,400,40,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 18:{
            if(battle(attacknum,defencenum,700,26,4,10)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,700,26,4,10);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 19:{
            if(battle(attacknum,defencenum,1000,108,0,99)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,1000,108,0,99);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 20:{
            if(battle(attacknum,defencenum,444,18,18,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,444,18,18,1);statusnum[2]->display(HPnum);
                goldnum+=4;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 21:{
            if(battle(attacknum,magicdefencenum,800,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 22:{
            if(battle(attacknum,magicdefencenum,120,30,60,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,120,30,60,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 23:{
            if(battle(attacknum,magicdefencenum,360,60,90,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,360,60,90,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 24:{
            if(battle(attacknum,magicdefencenum,800,80,120,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,120,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 25:{
            if(battle(attacknum,defencenum,555,15,20,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,555,15,20,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 26:{
            if(battle(attacknum,defencenum,777,30,40,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,777,30,40,1);statusnum[2]->display(HPnum);
                goldnum+=12;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 27:{
            if(battle(attacknum,defencenum,999,60,80,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,999,60,80,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 28:{
            if(battle(attacknum,magicdefencenum,1500,70,35,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,70,35,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 29:{
            if(battle(attacknum,magicdefencenum,3000,140,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,3000,140,0,1);statusnum[2]->display(HPnum);
                goldnum+=50;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 30:{
            if(battle(attacknum,magicdefencenum,888,88,88,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,888,88,88,1);statusnum[2]->display(HPnum);
                goldnum+=30;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 31:{
            if(yinggang){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;break;
            }
        }
        case 32:{
            if(longgang){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;break;
            }
        }
        case 33:{
            if(battle(attacknum,magicdefencenum,1500,200,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,200,0,1);statusnum[2]->display(HPnum);
                goldnum+=100;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 34:{
            if(battle(attacknum,defencenum,5000,500,200,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,5000,500,200,1);statusnum[2]->display(HPnum);
                goldnum+=200;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 35:{
            if(battle(attacknum,defencenum,3000,800,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,3000,800,0,1);statusnum[2]->display(HPnum);
                goldnum+=9999;expnum++;Xposition[floornum-1]++;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
                break;
            }
        }
        case 36:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;longgang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 37:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;yinggang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 38:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;attacknum+=20;
            statusnum[3]->display(attacknum);break;
        }
        case 39:{
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;defencenum+=20;
            statusnum[4]->display(defencenum);break;
        }
        case 101:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=9;table[3][2][9]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][3]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        case 102:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[9][j][k]->show();
                }
            }
            floornum=10;statusnum[0]->display(9999);
            break;
        }
        case 111:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=3;table[3][2][3]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][9]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        default:
            table[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerright.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]+1][Yposition[floornum-1]]=-1;Xposition[floornum-1]++;break;
        }
    }else if(e->key() == Qt::Key_W){
        switch (isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]) {
        case -104:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
            NPCtext[3]->setText("30 gold, you can get:");NPCtext[3]->show();
            NPCchoice[3][0]->setText("5 magicdefence");NPCchoice[3][0]->show();
            NPCchoice[3][1]->setText("Exit");NPCchoice[3][1]->show();
            break;
        }
        case -103:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
            NPCtext[2]->setText("50 gold, you can get:");NPCtext[2]->show();
            NPCchoice[2][0]->setText("1 yellowkey");NPCchoice[2][0]->show();
            NPCchoice[2][1]->setText("1 bluekey");NPCchoice[2][1]->show();
            NPCchoice[2][2]->setText("1 redkey");NPCchoice[2][2]->show();
            NPCchoice[2][3]->setText("Exit");NPCchoice[2][3]->show();
            break;
        }
        case -102:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
            NPCtext[1]->setText("Welcome, you can get:");NPCtext[1]->show();
            NPCchoice[1][0]->setText("5 attack");NPCchoice[1][0]->show();
            NPCchoice[1][1]->setText("7 defence");NPCchoice[1][1]->show();
            NPCchoice[1][2]->setText("1000 HP");NPCchoice[1][2]->show();
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
            break;
        }
        case -101:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
            NPCtext[0]->setText("50 gold, you can get:");NPCtext[0]->show();
            NPCchoice[0][0]->setText("5 attack");NPCchoice[0][0]->show();
            NPCchoice[0][1]->setText("7 defence");NPCchoice[0][1]->show();
            NPCchoice[0][2]->setText("1000 HP");NPCchoice[0][2]->show();
            NPCchoice[0][3]->setText("Exit");NPCchoice[0][3]->show();
            break;
        }
        case -9:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;defencenum+=5;
            statusnum[4]->display(defencenum);break;
        }
        case -8:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;attacknum+=5;
            statusnum[3]->display(attacknum);break;
        }
        case -7:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;magicdefencenum+=10;
            statusnum[5]->display(magicdefencenum);break;
        }
        case -6:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;HPnum+=200;
            statusnum[2]->display(HPnum);break;
        }
        case -5:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;redkeynum++;
            statusnum[10]->display(redkeynum);break;
        }
        case -4:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;bluekeynum++;
            statusnum[9]->display(bluekeynum);break;
        }
        case -3:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;yellowkeynum++;
            statusnum[8]->display(yellowkeynum);break;
        }
        case -2:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
            NPCtext[4]->setText("Thank you for saving me!");NPCtext[4]->show();
            NPCchoice[4][0]->setText("Exit");NPCchoice[4][0]->show();
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
            break;
        }
        case -1:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;break;
        }
        case 0:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
            break;
        }
        case 1:{
            if(yellowkeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;yellowkeynum--;
                statusnum[8]->display(yellowkeynum);break;
            }else{
                break;
            }
        }
        case 2:{
            if(bluekeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;bluekeynum--;
                statusnum[9]->display(bluekeynum);break;
            }else{
                break;
            }
        }
        case 3:{
            if(redkeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;redkeynum--;
                statusnum[10]->display(redkeynum);break;
            }else{
                break;
            }
        }
        case 4:{
            if(greenkeynum>0){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;greenkeynum--;
                statusnum[11]->display(greenkeynum);break;
            }else{
                break;
            }
        }
        case 5:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;attacknum++;
            statusnum[3]->display(attacknum);break;
        }
        case 6:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;defencenum++;
            statusnum[4]->display(defencenum);break;
        }
        case 7:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;HPnum+=500;
            statusnum[2]->display(HPnum);break;
        }
        case 8:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;HPnum+=1000;
            statusnum[2]->display(HPnum);break;
        }
        case 9:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;break;
        }
        case 10:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            break;
        }
        case 11:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            break;
        }
        case 12:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;HPnum-=100;
            statusnum[2]->display(HPnum);break;
        }
        case 13:{
            if(battle(attacknum,magicdefencenum,1000,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1000,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 14:{
            if(battle(attacknum,defencenum,100,15,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,100,15,0,1);statusnum[2]->display(HPnum);
                goldnum+=3;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 15:{
            if(battle(attacknum,defencenum,500,14,2,3)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,500,14,2,3);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 16:{
            if(battle(attacknum,magicdefencenum,200,20,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,200,20,0,1);statusnum[2]->display(HPnum);
                goldnum+=5;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 17:{
            if(battle(attacknum,magicdefencenum,400,40,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,400,40,0,1);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 18:{
            if(battle(attacknum,defencenum,700,26,4,10)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,700,26,4,10);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 19:{
            if(battle(attacknum,defencenum,1000,108,0,99)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,1000,108,0,99);statusnum[2]->display(HPnum);
                goldnum+=10;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 20:{
            if(battle(attacknum,defencenum,444,18,18,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,444,18,18,1);statusnum[2]->display(HPnum);
                goldnum+=4;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 21:{
            if(battle(attacknum,magicdefencenum,800,80,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,0,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 22:{
            if(battle(attacknum,magicdefencenum,120,30,60,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,120,30,60,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 23:{
            if(battle(attacknum,magicdefencenum,360,60,90,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,360,60,90,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 24:{
            if(battle(attacknum,magicdefencenum,800,80,120,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,800,80,120,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 25:{
            if(battle(attacknum,defencenum,555,15,20,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,555,15,20,1);statusnum[2]->display(HPnum);
                goldnum+=7;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 26:{
            if(battle(attacknum,defencenum,777,30,40,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,777,30,40,1);statusnum[2]->display(HPnum);
                goldnum+=12;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 27:{
            if(battle(attacknum,defencenum,999,60,80,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,999,60,80,1);statusnum[2]->display(HPnum);
                goldnum+=15;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 28:{
            if(battle(attacknum,magicdefencenum,1500,70,35,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,70,35,1);statusnum[2]->display(HPnum);
                goldnum+=20;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 29:{
            if(battle(attacknum,magicdefencenum,3000,140,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,3000,140,0,1);statusnum[2]->display(HPnum);
                goldnum+=50;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 30:{
            if(battle(attacknum,magicdefencenum,888,88,88,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,888,88,88,1);statusnum[2]->display(HPnum);
                goldnum+=30;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 31:{
            if(yinggang){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;break;
            }
        }
        case 32:{
            if(longgang){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;break;
            }
        }
        case 33:{
            if(battle(attacknum,magicdefencenum,1500,200,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,magicdefencenum,1500,200,0,1);statusnum[2]->display(HPnum);
                goldnum+=100;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 34:{
            if(battle(attacknum,defencenum,5000,500,200,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,5000,500,200,1);statusnum[2]->display(HPnum);
                goldnum+=200;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 35:{
            if(battle(attacknum,defencenum,3000,800,0,1)<HPnum){
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
                isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;
                HPnum=HPnum-battle(attacknum,defencenum,3000,800,0,1);statusnum[2]->display(HPnum);
                goldnum+=9999;expnum++;Yposition[floornum-1]--;statusnum[6]->display(expnum);
                statusnum[7]->display(goldnum);break;
            }else{
                table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/playerback.png);");
                break;
            }
        }
        case 36:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;longgang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 37:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;
            attacknum+=10;defencenum+=10;magicdefencenum+=10;yinggang++;
            statusnum[3]->display(attacknum);statusnum[4]->display(defencenum);statusnum[5]->display(magicdefencenum);
            break;
        }
        case 38:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;attacknum+=20;
            statusnum[3]->display(attacknum);break;
        }
        case 39:{
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;defencenum+=20;
            statusnum[4]->display(defencenum);break;
        }
        case 101:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum][j][k]->show();
                }
            }
            floornum++;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=9;table[3][2][9]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][3]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        case 102:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[9][j][k]->show();
                }
            }
            floornum=10;statusnum[0]->display(9999);
            break;
        }
        case 111:{
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                    table[floornum-2][j][k]->show();
                }
            }
            floornum--;statusnum[0]->display(floornum);
            Xposition[3]=2;Yposition[3]=3;table[3][2][3]->setStyleSheet("border-image: url(:/player.png);");
            table[3][2][9]->setStyleSheet("border-image: url(:/floor.png);");
            break;
        }
        default:
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]->setStyleSheet("border-image: url(:/playerback.png);");
            table[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]]->setStyleSheet("border-image: url(:/floor.png);");
            isWall[floornum-1][Xposition[floornum-1]][Yposition[floornum-1]-1]=-1;Yposition[floornum-1]--;break;
        }
    }else if(e->key() == Qt::Key_X){
        monster[0][0]->setStyleSheet("border-image: url(:/13monster.png);");
        monster[0][1]->setStyleSheet("border-image: url(:/14monster.png);");
        monster[0][2]->setStyleSheet("border-image: url(:/15monster.png);");
        monster[0][3]->setStyleSheet("border-image: url(:/16monster.png);");
        monster[0][4]->setStyleSheet("border-image: url(:/17monster.png);");
        monster[0][5]->setStyleSheet("border-image: url(:/18monster.png);");
        monster[0][6]->setStyleSheet("border-image: url(:/19monster.png);");
        monster[0][7]->setStyleSheet("border-image: url(:/20monster.png);");
        monster[0][8]->setStyleSheet("border-image: url(:/21monster.png);");
        monster[0][9]->setStyleSheet("border-image: url(:/22monster.png);");
        monster[0][10]->setStyleSheet("border-image: url(:/23monster.png);");
        monster[0][11]->setStyleSheet("border-image: url(:/24monster.png);");
        monster[1][0]->setStyleSheet("border-image: url(:/25monster.png);");
        monster[1][1]->setStyleSheet("border-image: url(:/26monster.png);");
        monster[1][2]->setStyleSheet("border-image: url(:/27monster.png);");
        monster[1][3]->setStyleSheet("border-image: url(:/28monster.png);");
        monster[1][4]->setStyleSheet("border-image: url(:/29monster.png);");
        monster[1][5]->setStyleSheet("border-image: url(:/30monster.png);");
        monster[1][6]->setStyleSheet("border-image: url(:/31monster.png);");
        monster[1][7]->setStyleSheet("border-image: url(:/32monster.png);");
        monster[1][8]->setStyleSheet("border-image: url(:/33monster.png);");
        monster[1][9]->setStyleSheet("border-image: url(:/34monster.png);");
        monster[1][10]->setStyleSheet("border-image: url(:/35monster.png);");
        monsternum[0][0]->display(battle(attacknum,magicdefencenum,1000,80,0,1));
        monsternum[0][1]->display(battle(attacknum,defencenum,100,15,0,1));
        monsternum[0][2]->display(battle(attacknum,defencenum,500,14,2,3));
        monsternum[0][3]->display(battle(attacknum,magicdefencenum,200,20,0,1));
        monsternum[0][4]->display(battle(attacknum,magicdefencenum,400,40,0,1));
        monsternum[0][5]->display(battle(attacknum,defencenum,700,26,4,10));
        monsternum[0][6]->display(battle(attacknum,defencenum,1000,108,0,99));
        monsternum[0][7]->display(battle(attacknum,defencenum,444,18,18,1));
        monsternum[0][8]->display(battle(attacknum,magicdefencenum,800,80,0,1));
        monsternum[0][9]->display(battle(attacknum,magicdefencenum,120,30,60,1));
        monsternum[0][10]->display(battle(attacknum,magicdefencenum,360,60,90,1));
        monsternum[0][11]->display(battle(attacknum,magicdefencenum,800,80,120,1));
        monsternum[1][0]->display(battle(attacknum,defencenum,555,15,20,1));
        monsternum[1][1]->display(battle(attacknum,defencenum,777,30,40,1));
        monsternum[1][2]->display(battle(attacknum,defencenum,999,60,80,1));
        monsternum[1][3]->display(battle(attacknum,magicdefencenum,1500,70,35,1));
        monsternum[1][4]->display(battle(attacknum,magicdefencenum,3000,140,0,1));
        monsternum[1][5]->display(battle(attacknum,magicdefencenum,888,88,88,1));
        monsternum[1][6]->display(battle(attacknum,defencenum,2000,456,654,1));
        monsternum[1][7]->display(battle(attacknum,defencenum,2000,654,456,1));
        monsternum[1][8]->display(battle(attacknum,magicdefencenum,1500,200,0,1));
        monsternum[1][9]->display(battle(attacknum,defencenum,5000,500,200,1));
        monsternum[1][10]->display(battle(attacknum,defencenum,3000,800,0,1));
        if(Xkeycount==0){
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                }
            }
            for(i=0;i<2;i++){
                for(j=0;j<12;j++){
                    monster[i][j]->show();
                    monsternum[i][j]->show();
                }
            }
            monsternum[1][11]->hide();
            Xkeycount=1;
        }else{
            for(i=0;i<2;i++){
                for(j=0;j<12;j++){
                    monster[i][j]->hide();
                    monsternum[i][j]->hide();
                }
            }
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->show();
                }
            }
            Xkeycount=0;
        }
    }else if(e->key() == Qt::Key_Z){
        thing[0][0]->setStyleSheet("border-image: url(:/1yellowdoor.png);");thingx[0][0]->setText("yellow door");
        thing[0][1]->setStyleSheet("border-image: url(:/2bluedoor.png);");thingx[0][1]->setText("blue door");
        thing[0][2]->setStyleSheet("border-image: url(:/3reddoor.png);");thingx[0][2]->setText("red door");
        thing[0][3]->setStyleSheet("border-image: url(:/-3yellowkey.png);");thingx[0][3]->setText("yellow key");
        thing[0][4]->setStyleSheet("border-image: url(:/-4bluekey.png);");thingx[0][4]->setText("blue key");
        thing[0][5]->setStyleSheet("border-image: url(:/-5redkey.png);");thingx[0][5]->setText("red key");
        thing[0][6]->setStyleSheet("border-image: url(:/5attack.png);");thingx[0][6]->setText("attack+1");
        thing[0][7]->setStyleSheet("border-image: url(:/6defence.png);");thingx[0][7]->setText("defence+1");
        thing[0][8]->setStyleSheet("border-image: url(:/-7magicdenfence.png);");thingx[0][8]->setText("magicdef+10");
        thing[0][9]->setStyleSheet("border-image: url(:/-8bigattack.png);");thingx[0][9]->setText("attack+5");
        thing[1][0]->setStyleSheet("border-image: url(:/-9bigdefence.png);");thingx[1][0]->setText("defence+5");
        thing[1][1]->setStyleSheet("border-image: url(:/9flowerdoor.png);");thingx[1][1]->setText("flower door");
        thing[1][2]->setStyleSheet("border-image: url(:/10upstair.png);");thingx[1][2]->setText("upstair");
        thing[1][3]->setStyleSheet("border-image: url(:/11downstair.png);");thingx[1][3]->setText("downstair");
        thing[1][4]->setStyleSheet("border-image: url(:/-6bluebottle.png);");thingx[1][4]->setText("HP+200");
        thing[1][5]->setStyleSheet("border-image: url(:/7yellowbottle.png);");thingx[1][5]->setText("HP+500");
        thing[1][6]->setStyleSheet("border-image: url(:/8greenbottle.png);");thingx[1][6]->setText("HP+1000");
        thing[1][7]->setStyleSheet("border-image: url(:/12lavafloor.png);");thingx[1][7]->setText("HP-100");
        thing[1][8]->setStyleSheet("border-image: url(:/13monster.png);");thingx[1][8]->setText("");
        thing[1][9]->setStyleSheet("border-image: url(:/14monster.png);");thingx[1][9]->setText("");
        thing[2][0]->setStyleSheet("border-image: url(:/15monster.png);");thingx[2][0]->setText("");
        thing[2][1]->setStyleSheet("border-image: url(:/16monster.png);");thingx[2][1]->setText("");
        thing[2][2]->setStyleSheet("border-image: url(:/17monster.png);");thingx[2][2]->setText("");
        thing[2][3]->setStyleSheet("border-image: url(:/18monster.png);");thingx[2][3]->setText("");
        thing[2][4]->setStyleSheet("border-image: url(:/19monster.png);");thingx[2][4]->setText("");
        thing[2][5]->setStyleSheet("border-image: url(:/20monster.png);");thingx[2][5]->setText("");
        thing[2][6]->setStyleSheet("border-image: url(:/21monster.png);");thingx[2][6]->setText("");
        thing[2][7]->setStyleSheet("border-image: url(:/22monster.png);");thingx[2][7]->setText("");
        thing[2][8]->setStyleSheet("border-image: url(:/23monster.png);");thingx[2][8]->setText("");
        thing[2][9]->setStyleSheet("border-image: url(:/24monster.png);");thingx[2][9]->setText("");
        thing[3][0]->setStyleSheet("border-image: url(:/25monster.png);");thingx[3][0]->setText("");
        thing[3][1]->setStyleSheet("border-image: url(:/26monster.png);");thingx[3][1]->setText("");
        thing[3][2]->setStyleSheet("border-image: url(:/27monster.png);");thingx[3][2]->setText("");
        thing[3][3]->setStyleSheet("border-image: url(:/28monster.png);");thingx[3][3]->setText("");
        thing[3][4]->setStyleSheet("border-image: url(:/29monster.png);");thingx[3][4]->setText("");
        thing[3][5]->setStyleSheet("border-image: url(:/30monster.png);");thingx[3][5]->setText("");
        thing[3][6]->setStyleSheet("border-image: url(:/31monster.png);");thingx[3][6]->setText("");
        thing[3][7]->setStyleSheet("border-image: url(:/32monster.png);");thingx[3][7]->setText("");
        thing[3][8]->setStyleSheet("border-image: url(:/33monster.png);");thingx[3][8]->setText("");
        thing[3][9]->setStyleSheet("border-image: url(:/34monster.png);");thingx[3][9]->setText("");
        thing[4][0]->setStyleSheet("border-image: url(:/35monster.png);");thingx[4][0]->setText("");
        thing[4][1]->setStyleSheet("border-image: url(:/36longgang.png);");thingx[4][1]->setText("kill dragon");
        thing[4][2]->setStyleSheet("border-image: url(:/37yinggang.png);");thingx[4][2]->setText("kill shadow");
        thing[4][3]->setStyleSheet("border-image: url(:/38shenshengye.png);");thingx[4][3]->setText("attack+20");
        thing[4][4]->setStyleSheet("border-image: url(:/39liumangxing.png);");thingx[4][4]->setText("defence+20");
        thing[4][5]->setStyleSheet("border-image: url(:/NPC1.png);");thingx[4][5]->setText("NPC");
        thing[4][6]->setStyleSheet("border-image: url(:/NPC2.png);");thingx[4][6]->setText("store");
        thing[4][7]->setStyleSheet("border-image: url(:/star.png);");thingx[4][7]->setText("star");
        thing[4][8]->setStyleSheet("border-image: url(:/wall.png);");thingx[4][8]->setText("wall");
        thing[4][9]->setStyleSheet("border-image: url(:/floor.png);");thingx[4][9]->setText("floor");
        if(Zkeycount==0){
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->hide();
                }
            }
            for(i=0;i<5;i++){
                for(j=0;j<10;j++){
                    thing[i][j]->show();
                    thingx[i][j]->show();
                }
            }
            Zkeycount=1;
        }else{
            for(i=0;i<5;i++){
                for(j=0;j<10;j++){
                    thing[i][j]->hide();
                    thingx[i][j]->hide();
                }
            }
            for(j=0;j<13;j++){
                for(k=0;k<13;k++){
                    table[floornum-1][j][k]->show();
                }
            }
            Zkeycount=0;
        }
    }
}
int MainWindow::battle(int b,int c,int d,int e,int f,int g)
{
    int myatt=b,mydef=c,hehp=d,heatt=e,hedef=f,hetime=g;
    int manage=0;
    if(myatt>hedef){
        do{
            hehp=hehp-myatt+hedef;
            if(hehp>0){
                for(int i=0;i<hetime;i++){
                    manage=manage+heatt-mydef;
                }
            }
        }while(hehp>0);
    }else{
        manage=9999999;
    }
    if(manage>0){
        return manage;
    }else{
        return manage=0;
    }
}
void MainWindow::setplayer()
{
    Xposition[0]=10;Xposition[1]=3;Xposition[2]=6;Xposition[3]=2;Xposition[4]=9;
    Xposition[5]=10;Xposition[6]=9;Xposition[7]=9;Xposition[8]=10;Xposition[9]=6;
    Yposition[0]=6;Yposition[1]=2;Yposition[2]=10;Yposition[3]=3;Yposition[4]=6;
    Yposition[5]=6;Yposition[6]=6;Yposition[7]=6;Yposition[8]=6;Yposition[9]=6;
    table[0][10][6]->setStyleSheet("border-image: url(:/player.png);");
    table[1][3][2]->setStyleSheet("border-image: url(:/player.png);");
    table[2][6][10]->setStyleSheet("border-image: url(:/player.png);");
    table[3][2][3]->setStyleSheet("border-image: url(:/player.png);");
    table[4][9][6]->setStyleSheet("border-image: url(:/player.png);");
    table[5][10][6]->setStyleSheet("border-image: url(:/player.png);");
    table[6][9][6]->setStyleSheet("border-image: url(:/player.png);");
    table[7][9][6]->setStyleSheet("border-image: url(:/player.png);");
    table[8][10][6]->setStyleSheet("border-image: url(:/player.png);");
    table[9][6][6]->setStyleSheet("border-image: url(:/player.png);");
}
void MainWindow::setstatus()
{
    floornum=1;levelnum=1;HPnum=1000;attacknum=10;defencenum=10;magicdefencenum=0;
    expnum=0;goldnum=0;yellowkeynum=0;bluekeynum=0;redkeynum=0;greenkeynum=0;
    QFont ft;
    ft.setPointSize(12);
    for(i=0;i<12;i++){
        status[i]->setStyleSheet("color:white;");
        status[i]->setFont(ft);
        statusnum[i]->setStyleSheet("color:white;");
    }
    status[0]->setText("Floor");
    status[1]->setText("Level");
    status[2]->setText("HP");
    status[3]->setText("Attack");
    status[4]->setText("Defence");
    status[5]->setText("MagicDef");
    status[6]->setText("Exp");
    status[7]->setText("Gold");
    status[8]->setText("YellowKey");
    status[9]->setText("BlueKey");
    status[10]->setText("RedKey");
    status[11]->setText("GreenKey");
    statusnum[0]->display(floornum);
    statusnum[1]->display(levelnum);
    statusnum[2]->display(HPnum);
    statusnum[3]->display(attacknum);
    statusnum[4]->display(defencenum);
    statusnum[5]->display(magicdefencenum);
    statusnum[6]->display(expnum);
    statusnum[7]->display(goldnum);
    statusnum[8]->display(yellowkeynum);
    statusnum[9]->display(bluekeynum);
    statusnum[10]->display(redkeynum);
    statusnum[11]->display(greenkeynum);
}
void MainWindow::settable1()
{
    table[0][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][0]=0;
    table[0][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][1]=0;
    table[0][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][2]=0;
    table[0][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][3]=0;
    table[0][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][4]=0;
    table[0][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][5]=0;
    table[0][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][6]=0;
    table[0][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][7]=0;
    table[0][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][8]=0;
    table[0][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][9]=0;
    table[0][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][10]=0;
    table[0][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][11]=0;
    table[0][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][0][12]=0;
    table[0][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][1][0]=0;
    table[0][1][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][1]=0;
    table[0][1][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][2]=0;
    table[0][1][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][3]=0;
    table[0][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][4]=0;
    table[0][1][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][5]=0;
    table[0][1][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][6]=0;
    table[0][1][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][7]=0;
    table[0][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][8]=0;
    table[0][1][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][9]=0;
    table[0][1][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][10]=0;
    table[0][1][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][1][11]=0;
    table[0][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][1][12]=0;
    table[0][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][2][0]=0;
    table[0][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][1]=0;
    table[0][2][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][2]=0;
    table[0][2][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][3]=0;
    table[0][2][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][4]=0;
    table[0][2][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][5]=0;
    table[0][2][6]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[0][2][6]=10;
    table[0][2][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][7]=0;
    table[0][2][8]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][2][8]=5;
    table[0][2][9]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][2][9]=5;
    table[0][2][10]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][2][10]=5;
    table[0][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][2][11]=0;
    table[0][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][2][12]=0;
    table[0][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][3][0]=0;
    table[0][3][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][3][1]=0;
    table[0][3][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][3][2]=0;
    table[0][3][3]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[0][3][3]=-2;
    table[0][3][4]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[0][3][4]=8;
    table[0][3][5]->setStyleSheet("border-image: url(:/15monster.png);"); isWall[0][3][5]=15;
    table[0][3][6]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[0][3][6]=12;
    table[0][3][7]->setStyleSheet("border-image: url(:/15monster.png);"); isWall[0][3][7]=15;
    table[0][3][8]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][3][8]=6;
    table[0][3][9]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][3][9]=6;
    table[0][3][10]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][3][10]=6;
    table[0][3][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][3][11]=0;
    table[0][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][3][12]=0;
    table[0][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][4][0]=0;
    table[0][4][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][1]=0;
    table[0][4][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][2]=0;
    table[0][4][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][3]=0;
    table[0][4][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][4]=0;
    table[0][4][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][5]=0;
    table[0][4][6]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[0][4][6]=14;
    table[0][4][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][7]=0;
    table[0][4][8]->setStyleSheet("border-image: url(:/7yellowbottle.png);"); isWall[0][4][8]=7;
    table[0][4][9]->setStyleSheet("border-image: url(:/7yellowbottle.png);"); isWall[0][4][9]=7;
    table[0][4][10]->setStyleSheet("border-image: url(:/7yellowbottle.png);"); isWall[0][4][10]=7;
    table[0][4][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][4][11]=0;
    table[0][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][4][12]=0;
    table[0][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][5][0]=0;
    table[0][5][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][1]=0;
    table[0][5][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][2]=0;
    table[0][5][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][3]=0;
    table[0][5][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][4]=0;
    table[0][5][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][5]=0;
    table[0][5][6]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[0][5][6]=9;
    table[0][5][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][7]=0;
    table[0][5][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][8]=0;
    table[0][5][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][9]=0;
    table[0][5][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][10]=0;
    table[0][5][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][5][11]=0;
    table[0][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][5][12]=0;
    table[0][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][6][0]=0;
    table[0][6][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][6][1]=0;
    table[0][6][2]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][6][2]=5;
    table[0][6][3]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][6][3]=5;
    table[0][6][4]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[0][6][4]=14;
    table[0][6][5]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[0][6][5]=14;
    table[0][6][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[0][6][6]=8;
    table[0][6][7]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[0][6][7]=14;
    table[0][6][8]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[0][6][8]=14;
    table[0][6][9]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][6][9]=6;
    table[0][6][10]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][6][10]=6;
    table[0][6][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][6][11]=0;
    table[0][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][6][12]=0;
    table[0][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][7][0]=0;
    table[0][7][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][1]=0;
    table[0][7][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][2]=0;
    table[0][7][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][3]=0;
    table[0][7][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][4]=0;
    table[0][7][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][5]=0;
    table[0][7][6]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[0][7][6]=9;
    table[0][7][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][7]=0;
    table[0][7][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][8]=0;
    table[0][7][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][9]=0;
    table[0][7][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][10]=0;
    table[0][7][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][7][11]=0;
    table[0][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][7][12]=0;
    table[0][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][8][0]=0;
    table[0][8][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][1]=0;
    table[0][8][2]->setStyleSheet("border-image: url(:/7yellowbottle.png);"); isWall[0][8][2]=7;
    table[0][8][3]->setStyleSheet("border-image: url(:/7yellowbottle.png);"); isWall[0][8][3]=7;
    table[0][8][4]->setStyleSheet("border-image: url(:/7yellowbottle.png);"); isWall[0][8][4]=7;
    table[0][8][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][5]=0;
    table[0][8][6]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[0][8][6]=14;
    table[0][8][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][7]=0;
    table[0][8][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][8]=0;
    table[0][8][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][9]=0;
    table[0][8][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][10]=0;
    table[0][8][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][8][11]=0;
    table[0][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][8][12]=0;
    table[0][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][9][0]=0;
    table[0][9][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][9][1]=0;
    table[0][9][2]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][9][2]=6;
    table[0][9][3]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][9][3]=6;
    table[0][9][4]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[0][9][4]=6;
    table[0][9][5]->setStyleSheet("border-image: url(:/15monster.png);"); isWall[0][9][5]=15;
    table[0][9][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[0][9][6]=-1;
    table[0][9][7]->setStyleSheet("border-image: url(:/15monster.png);"); isWall[0][9][7]=15;
    table[0][9][8]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[0][9][8]=8;
    table[0][9][9]->setStyleSheet("border-image: url(:/13monster.png);"); isWall[0][9][9]=13;
    table[0][9][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][9][10]=0;
    table[0][9][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][9][11]=0;
    table[0][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][9][12]=0;
    table[0][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][10][0]=0;
    table[0][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][1]=0;
    table[0][10][2]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][10][2]=5;
    table[0][10][3]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][10][3]=5;
    table[0][10][4]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[0][10][4]=5;
    table[0][10][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][5]=0;
    table[0][10][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[0][10][6]=-1;
    table[0][10][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][7]=0;
    table[0][10][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][8]=0;
    table[0][10][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][9]=0;
    table[0][10][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][10]=0;
    table[0][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][10][11]=0;
    table[0][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][10][12]=0;
    table[0][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][11][0]=0;
    table[0][11][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][1]=0;
    table[0][11][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][2]=0;
    table[0][11][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][3]=0;
    table[0][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][4]=0;
    table[0][11][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][5]=0;
    table[0][11][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][6]=0;
    table[0][11][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][7]=0;
    table[0][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][8]=0;
    table[0][11][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][9]=0;
    table[0][11][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][10]=0;
    table[0][11][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[0][11][11]=0;
    table[0][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][11][12]=0;
    table[0][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][0]=0;
    table[0][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][1]=0;
    table[0][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][2]=0;
    table[0][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][3]=0;
    table[0][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][4]=0;
    table[0][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][5]=0;
    table[0][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][6]=0;
    table[0][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][7]=0;
    table[0][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][8]=0;
    table[0][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][9]=0;
    table[0][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][10]=0;
    table[0][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][11]=0;
    table[0][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[0][12][12]=0;
}
void MainWindow::settable2()
{
    table[1][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][0]=0;
    table[1][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][1]=0;
    table[1][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][2]=0;
    table[1][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][3]=0;
    table[1][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][4]=0;
    table[1][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][5]=0;
    table[1][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][6]=0;
    table[1][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][7]=0;
    table[1][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][8]=0;
    table[1][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][9]=0;
    table[1][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][10]=0;
    table[1][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][11]=0;
    table[1][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][0][12]=0;
    table[1][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][1][0]=0;
    table[1][1][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][1]=0;
    table[1][1][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][2]=0;
    table[1][1][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][3]=0;
    table[1][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][4]=0;
    table[1][1][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][5]=0;
    table[1][1][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][6]=0;
    table[1][1][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][7]=0;
    table[1][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][8]=0;
    table[1][1][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][9]=0;
    table[1][1][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][10]=0;
    table[1][1][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][1][11]=0;
    table[1][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][1][12]=0;
    table[1][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][2][0]=0;
    table[1][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][2][1]=0;
    table[1][2][2]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[1][2][2]=11;
    table[1][2][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][2][3]=0;
    table[1][2][4]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[1][2][4]=-2;
    table[1][2][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][2][5]=-1;
    table[1][2][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][2][6]=-1;
    table[1][2][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][2][7]=-1;
    table[1][2][8]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[1][2][8]=-2;
    table[1][2][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][2][9]=0;
    table[1][2][10]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[1][2][10]=5;
    table[1][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][2][11]=0;
    table[1][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][2][12]=0;
    table[1][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][3][0]=0;
    table[1][3][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][3][1]=0;
    table[1][3][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][3][2]=-1;
    table[1][3][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][3][3]=0;
    table[1][3][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][3][4]=-1;
    table[1][3][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][3][5]=-1;
    table[1][3][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][3][6]=-1;
    table[1][3][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][3][7]=-1;
    table[1][3][8]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][3][8]=-1;
    table[1][3][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][3][9]=0;
    table[1][3][10]->setStyleSheet("border-image: url(:/17monster.png);"); isWall[1][3][10]=17;
    table[1][3][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][3][11]=0;
    table[1][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][3][12]=0;
    table[1][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][4][0]=0;
    table[1][4][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][1]=0;
    table[1][4][2]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[1][4][2]=14;
    table[1][4][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][3]=0;
    table[1][4][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][4]=0;
    table[1][4][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][5]=0;
    table[1][4][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][6]=0;
    table[1][4][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][7]=0;
    table[1][4][8]->setStyleSheet("border-image: url(:/19monster.png);"); isWall[1][4][8]=19;
    table[1][4][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][9]=0;
    table[1][4][10]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[1][4][10]=6;
    table[1][4][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][4][11]=0;
    table[1][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][4][12]=0;
    table[1][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][5][0]=0;
    table[1][5][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][5][1]=0;
    table[1][5][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][2]=-1;
    table[1][5][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][3]=-1;
    table[1][5][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][4]=-1;
    table[1][5][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][5]=-1;
    table[1][5][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][6]=-1;
    table[1][5][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][7]=-1;
    table[1][5][8]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][5][8]=-1;
    table[1][5][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][5][9]=0;
    table[1][5][10]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[1][5][10]=16;
    table[1][5][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][5][11]=0;
    table[1][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][5][12]=0;
    table[1][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][6][0]=0;
    table[1][6][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][6][1]=0;
    table[1][6][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][2]=-1;
    table[1][6][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][3]=-1;
    table[1][6][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][4]=-1;
    table[1][6][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][5]=-1;
    table[1][6][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][6]=-1;
    table[1][6][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][7]=-1;
    table[1][6][8]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][6][8]=-1;
    table[1][6][9]->setStyleSheet("border-image: url(:/2bluedoor.png);"); isWall[1][6][9]=2;
    table[1][6][10]->setStyleSheet("border-image: url(:/20monster.png);"); isWall[1][6][10]=20;
    table[1][6][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][6][11]=0;
    table[1][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][6][12]=0;
    table[1][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][7][0]=0;
    table[1][7][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][7][1]=0;
    table[1][7][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][2]=-1;
    table[1][7][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][3]=-1;
    table[1][7][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][4]=-1;
    table[1][7][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][5]=-1;
    table[1][7][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][6]=-1;
    table[1][7][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][7]=-1;
    table[1][7][8]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][7][8]=-1;
    table[1][7][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][7][9]=0;
    table[1][7][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][7][10]=0;
    table[1][7][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][7][11]=0;
    table[1][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][7][12]=0;
    table[1][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][8][0]=0;
    table[1][8][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][1]=0;
    table[1][8][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][2]=0;
    table[1][8][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][3]=0;
    table[1][8][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][4]=0;
    table[1][8][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][5]=0;
    table[1][8][6]->setStyleSheet("border-image: url(:/18monster.png);"); isWall[1][8][6]=18;
    table[1][8][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][7]=0;
    table[1][8][8]->setStyleSheet("border-image: url(:/15monster.png);"); isWall[1][8][8]=15;
    table[1][8][9]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[1][8][9]=9;
    table[1][8][10]->setStyleSheet("border-image: url(:/-3yellowkey.png);"); isWall[1][8][10]=-3;
    table[1][8][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][8][11]=0;
    table[1][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][8][12]=0;
    table[1][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][9][0]=0;
    table[1][9][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][9][1]=0;
    table[1][9][2]->setStyleSheet("border-image: url(:/-4bluekey.png);"); isWall[1][9][2]=-4;
    table[1][9][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][9][3]=0;
    table[1][9][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][9][4]=-1;
    table[1][9][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][9][5]=-1;
    table[1][9][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][9][6]=-1;
    table[1][9][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][9][7]=0;
    table[1][9][8]->setStyleSheet("border-image: url(:/-6bluebottle.png);"); isWall[1][9][8]=-6;
    table[1][9][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][9][9]=0;
    table[1][9][10]->setStyleSheet("border-image: url(:/-3yellowkey.png);"); isWall[1][9][10]=-3;
    table[1][9][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][9][11]=0;
    table[1][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][9][12]=0;
    table[1][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][10][0]=0;
    table[1][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][10][1]=0;
    table[1][10][2]->setStyleSheet("border-image: url(:/-5redkey.png);"); isWall[1][10][2]=-5;
    table[1][10][3]->setStyleSheet("border-image: url(:/20monster.png);"); isWall[1][10][3]=20;
    table[1][10][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][10][4]=-1;
    table[1][10][5]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[1][10][5]=-2;
    table[1][10][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[1][10][6]=-1;
    table[1][10][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][10][7]=0;
    table[1][10][8]->setStyleSheet("border-image: url(:/NPC2.png);"); isWall[1][10][8]=-101;
    table[1][10][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][10][9]=0;
    table[1][10][10]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[1][10][10]=10;
    table[1][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][10][11]=0;
    table[1][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][10][12]=0;
    table[1][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][11][0]=0;
    table[1][11][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][1]=0;
    table[1][11][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][2]=0;
    table[1][11][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][3]=0;
    table[1][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][4]=0;
    table[1][11][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][5]=0;
    table[1][11][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][6]=0;
    table[1][11][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][7]=0;
    table[1][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][8]=0;
    table[1][11][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][9]=0;
    table[1][11][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][10]=0;
    table[1][11][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[1][11][11]=0;
    table[1][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][11][12]=0;
    table[1][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][0]=0;
    table[1][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][1]=0;
    table[1][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][2]=0;
    table[1][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][3]=0;
    table[1][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][4]=0;
    table[1][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][5]=0;
    table[1][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][6]=0;
    table[1][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][7]=0;
    table[1][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][8]=0;
    table[1][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][9]=0;
    table[1][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][10]=0;
    table[1][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][11]=0;
    table[1][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[1][12][12]=0;
}
void MainWindow::settable3()
{
    table[2][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][0]=0;
    table[2][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][1]=0;
    table[2][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][2]=0;
    table[2][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][3]=0;
    table[2][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][4]=0;
    table[2][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][5]=0;
    table[2][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][6]=0;
    table[2][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][7]=0;
    table[2][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][8]=0;
    table[2][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][9]=0;
    table[2][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][10]=0;
    table[2][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][11]=0;
    table[2][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][0][12]=0;
    table[2][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][1][0]=0;
    table[2][1][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][1]=0;
    table[2][1][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][2]=0;
    table[2][1][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][3]=0;
    table[2][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][4]=0;
    table[2][1][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][5]=0;
    table[2][1][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][6]=0;
    table[2][1][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][7]=0;
    table[2][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][8]=0;
    table[2][1][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][9]=0;
    table[2][1][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][10]=0;
    table[2][1][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][1][11]=0;
    table[2][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][1][12]=0;
    table[2][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][2][0]=0;
    table[2][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][2][1]=0;
    table[2][2][2]->setStyleSheet("border-image: url(:/17monster.png);"); isWall[2][2][2]=17;
    table[2][2][3]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][2][3]=5;
    table[2][2][4]->setStyleSheet("border-image: url(:/17monster.png);"); isWall[2][2][4]=17;
    table[2][2][5]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][2][5]=5;
    table[2][2][6]->setStyleSheet("border-image: url(:/17monster.png);"); isWall[2][2][6]=17;
    table[2][2][7]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][2][7]=5;
    table[2][2][8]->setStyleSheet("border-image: url(:/17monster.png);"); isWall[2][2][8]=17;
    table[2][2][9]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][2][9]=5;
    table[2][2][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][2][10]=0;
    table[2][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][2][11]=0;
    table[2][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][2][12]=0;
    table[2][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][3][0]=0;
    table[2][3][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][1]=0;
    table[2][3][2]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][3][2]=5;
    table[2][3][3]->setStyleSheet("border-image: url(:/17monster.png);"); isWall[2][3][3]=17;
    table[2][3][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][4]=0;
    table[2][3][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][5]=0;
    table[2][3][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][6]=0;
    table[2][3][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][7]=0;
    table[2][3][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][8]=0;
    table[2][3][9]->setStyleSheet("border-image: url(:/NPC2.png);"); isWall[2][3][9]=-102;
    table[2][3][10]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][3][10]=5;
    table[2][3][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][3][11]=0;
    table[2][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][3][12]=0;
    table[2][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][4][0]=0;
    table[2][4][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][4][1]=0;
    table[2][4][2]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[2][4][2]=10;
    table[2][4][3]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][4][3]=5;
    table[2][4][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][4][4]=0;
    table[2][4][5]->setStyleSheet("border-image: url(:/22monster.png);"); isWall[2][4][5]=22;
    table[2][4][6]->setStyleSheet("border-image: url(:/23monster.png);"); isWall[2][4][6]=23;
    table[2][4][7]->setStyleSheet("border-image: url(:/22monster.png);"); isWall[2][4][7]=22;
    table[2][4][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][4][8]=0;
    table[2][4][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][4][9]=0;
    table[2][4][10]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[2][4][10]=16;
    table[2][4][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][4][11]=0;
    table[2][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][4][12]=0;
    table[2][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][5][0]=0;
    table[2][5][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][5][1]=0;
    table[2][5][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][5][2]=0;
    table[2][5][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][5][3]=0;
    table[2][5][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][5][4]=0;
    table[2][5][5]->setStyleSheet("border-image: url(:/23monster.png);"); isWall[2][5][5]=23;
    table[2][5][6]->setStyleSheet("border-image: url(:/36longgang.png);"); isWall[2][5][6]=36;
    table[2][5][7]->setStyleSheet("border-image: url(:/23monster.png);"); isWall[2][5][7]=23;
    table[2][5][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][5][8]=0;
    table[2][5][9]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[2][5][9]=16;
    table[2][5][10]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[2][5][10]=16;
    table[2][5][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][5][11]=0;
    table[2][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][5][12]=0;
    table[2][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][6][0]=0;
    table[2][6][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][6][1]=0;
    table[2][6][2]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[2][6][2]=101;
    table[2][6][3]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[2][6][3]=3;
    table[2][6][4]->setStyleSheet("border-image: url(:/24monster.png);"); isWall[2][6][4]=24;
    table[2][6][5]->setStyleSheet("border-image: url(:/22monster.png);"); isWall[2][6][5]=22;
    table[2][6][6]->setStyleSheet("border-image: url(:/23monster.png);"); isWall[2][6][6]=23;
    table[2][6][7]->setStyleSheet("border-image: url(:/22monster.png);"); isWall[2][6][7]=22;
    table[2][6][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][6][8]=0;
    table[2][6][9]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[2][6][9]=11;
    table[2][6][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[2][6][10]=-1;
    table[2][6][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][6][11]=0;
    table[2][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][6][12]=0;
    table[2][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][7][0]=0;
    table[2][7][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][1]=0;
    table[2][7][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][2]=0;
    table[2][7][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][3]=0;
    table[2][7][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][4]=0;
    table[2][7][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][5]=0;
    table[2][7][6]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][7][6]=5;
    table[2][7][7]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[2][7][7]=6;
    table[2][7][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][8]=0;
    table[2][7][9]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[2][7][9]=16;
    table[2][7][10]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[2][7][10]=16;
    table[2][7][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][7][11]=0;
    table[2][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][7][12]=0;
    table[2][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][8][0]=0;
    table[2][8][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][8][1]=0;
    table[2][8][2]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[2][8][2]=8;
    table[2][8][3]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[2][8][3]=8;
    table[2][8][4]->setStyleSheet("border-image: url(:/21monster.png);"); isWall[2][8][4]=21;
    table[2][8][5]->setStyleSheet("border-image: url(:/21monster.png);"); isWall[2][8][5]=21;
    table[2][8][6]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[2][8][6]=6;
    table[2][8][7]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[2][8][7]=5;
    table[2][8][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][8][8]=0;
    table[2][8][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][8][9]=0;
    table[2][8][10]->setStyleSheet("border-image: url(:/16monster.png);"); isWall[2][8][10]=16;
    table[2][8][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][8][11]=0;
    table[2][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][8][12]=0;
    table[2][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][9][0]=0;
    table[2][9][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][1]=0;
    table[2][9][2]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[2][9][2]=8;
    table[2][9][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][3]=0;
    table[2][9][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][4]=0;
    table[2][9][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][5]=0;
    table[2][9][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][6]=0;
    table[2][9][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][7]=0;
    table[2][9][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][8]=0;
    table[2][9][9]->setStyleSheet("border-image: url(:/NPC2.png);"); isWall[2][9][9]=-103;
    table[2][9][10]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[2][9][10]=6;
    table[2][9][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][9][11]=0;
    table[2][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][9][12]=0;
    table[2][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][10][0]=0;
    table[2][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][10][1]=0;
    table[2][10][2]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[2][10][2]=8;
    table[2][10][3]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[2][10][3]=8;
    table[2][10][4]->setStyleSheet("border-image: url(:/21monster.png);"); isWall[2][10][4]=21;
    table[2][10][5]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[2][10][5]=6;
    table[2][10][6]->setStyleSheet("border-image: url(:/21monster.png);"); isWall[2][10][6]=21;
    table[2][10][7]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[2][10][7]=6;
    table[2][10][8]->setStyleSheet("border-image: url(:/21monster.png);"); isWall[2][10][8]=21;
    table[2][10][9]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[2][10][9]=6;
    table[2][10][10]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[2][10][10]=12;
    table[2][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][10][11]=0;
    table[2][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][10][12]=0;
    table[2][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][11][0]=0;
    table[2][11][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][1]=0;
    table[2][11][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][2]=0;
    table[2][11][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][3]=0;
    table[2][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][4]=0;
    table[2][11][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][5]=0;
    table[2][11][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][6]=0;
    table[2][11][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][7]=0;
    table[2][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][8]=0;
    table[2][11][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][9]=0;
    table[2][11][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][10]=0;
    table[2][11][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[2][11][11]=0;
    table[2][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][11][12]=0;
    table[2][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][0]=0;
    table[2][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][1]=0;
    table[2][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][2]=0;
    table[2][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][3]=0;
    table[2][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][4]=0;
    table[2][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][5]=0;
    table[2][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][6]=0;
    table[2][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][7]=0;
    table[2][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][8]=0;
    table[2][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][9]=0;
    table[2][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][10]=0;
    table[2][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][11]=0;
    table[2][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[2][12][12]=0;
}
void MainWindow::settable4()
{
    table[3][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][0]=0;
    table[3][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][1]=0;
    table[3][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][2]=0;
    table[3][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][3]=0;
    table[3][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][4]=0;
    table[3][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][5]=0;
    table[3][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][6]=0;
    table[3][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][7]=0;
    table[3][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][8]=0;
    table[3][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][9]=0;
    table[3][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][10]=0;
    table[3][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][11]=0;
    table[3][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][0][12]=0;
    table[3][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][1][0]=0;
    table[3][1][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][1]=0;
    table[3][1][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][2]=0;
    table[3][1][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][3]=0;
    table[3][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][4]=0;
    table[3][1][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][5]=0;
    table[3][1][6]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[3][1][6]=10;
    table[3][1][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][7]=0;
    table[3][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][8]=0;
    table[3][1][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][9]=0;
    table[3][1][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][10]=0;
    table[3][1][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][1][11]=0;
    table[3][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][1][12]=0;
    table[3][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][2][0]=0;
    table[3][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][2][1]=0;
    table[3][2][2]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[3][2][2]=11;
    table[3][2][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[3][2][3]=-1;
    table[3][2][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][2][4]=0;
    table[3][2][5]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][2][5]=-7;
    table[3][2][6]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][2][6]=-7;
    table[3][2][7]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][2][7]=-7;
    table[3][2][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][2][8]=0;
    table[3][2][9]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][2][9]=-7;
    table[3][2][10]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[3][2][10]=111;
    table[3][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][2][11]=0;
    table[3][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][2][12]=0;
    table[3][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][3][0]=0;
    table[3][3][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][1]=0;
    table[3][3][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][2]=0;
    table[3][3][3]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][3][3]=-7;
    table[3][3][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][4]=0;
    table[3][3][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][5]=0;
    table[3][3][6]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[3][3][6]=3;
    table[3][3][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][7]=0;
    table[3][3][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][8]=0;
    table[3][3][9]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][3][9]=-7;
    table[3][3][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][10]=0;
    table[3][3][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][3][11]=0;
    table[3][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][3][12]=0;
    table[3][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][4][0]=0;
    table[3][4][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][4][1]=0;
    table[3][4][2]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][4][2]=-7;
    table[3][4][3]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[3][4][3]=-2;
    table[3][4][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][4][4]=0;
    table[3][4][5]->setStyleSheet("border-image: url(:/NPC2.png);"); isWall[3][4][5]=-104;
    table[3][4][6]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][4][6]=12;
    table[3][4][7]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[3][4][7]=-2;
    table[3][4][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][4][8]=0;
    table[3][4][9]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[3][4][9]=-2;
    table[3][4][10]->setStyleSheet("border-image: url(:/-7magicdenfence.png);"); isWall[3][4][10]=-7;
    table[3][4][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][4][11]=0;
    table[3][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][4][12]=0;
    table[3][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][5][0]=0;
    table[3][5][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][5][1]=0;
    table[3][5][2]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[3][5][2]=9;
    table[3][5][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][5][3]=0;
    table[3][5][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][5][4]=0;
    table[3][5][5]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][5][5]=12;
    table[3][5][6]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][5][6]=12;
    table[3][5][7]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][5][7]=12;
    table[3][5][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][5][8]=0;
    table[3][5][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][5][9]=0;
    table[3][5][10]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[3][5][10]=9;
    table[3][5][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][5][11]=0;
    table[3][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][5][12]=0;
    table[3][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][6][0]=0;
    table[3][6][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][6][1]=0;
    table[3][6][2]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[3][6][2]=-2;
    table[3][6][3]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[3][6][3]=8;
    table[3][6][4]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[3][6][4]=9;
    table[3][6][5]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][6][5]=12;
    table[3][6][6]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][6][6]=12;
    table[3][6][7]->setStyleSheet("border-image: url(:/12lavafloor.png);"); isWall[3][6][7]=12;
    table[3][6][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][6][8]=0;
    table[3][6][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][6][9]=102;
    table[3][6][10]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[3][6][10]=-2;
    table[3][6][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][6][11]=0;
    table[3][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][6][12]=0;
    table[3][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][7][0]=0;
    table[3][7][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][1]=0;
    table[3][7][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][2]=0;
    table[3][7][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][3]=0;
    table[3][7][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][4]=0;
    table[3][7][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][5]=0;
    table[3][7][6]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[3][7][6]=3;
    table[3][7][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][7]=0;
    table[3][7][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][8]=0;
    table[3][7][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][9]=0;
    table[3][7][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][10]=0;
    table[3][7][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][7][11]=0;
    table[3][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][7][12]=0;
    table[3][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][8][0]=0;
    table[3][8][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][8][1]=0;
    table[3][8][2]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][8][2]=6;
    table[3][8][3]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][8][3]=6;
    table[3][8][4]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][8][4]=6;
    table[3][8][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][8][5]=0;
    table[3][8][6]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[3][8][6]=3;
    table[3][8][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][8][7]=0;
    table[3][8][8]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][8][8]=5;
    table[3][8][9]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][8][9]=5;
    table[3][8][10]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][8][10]=5;
    table[3][8][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][8][11]=0;
    table[3][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][8][12]=0;
    table[3][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][9][0]=0;
    table[3][9][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][9][1]=0;
    table[3][9][2]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][9][2]=6;
    table[3][9][3]->setStyleSheet("border-image: url(:/39liumangxing.png);"); isWall[3][9][3]=39;
    table[3][9][4]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][9][4]=6;
    table[3][9][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][9][5]=0;
    table[3][9][6]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[3][9][6]=3;
    table[3][9][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][9][7]=0;
    table[3][9][8]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][9][8]=5;
    table[3][9][9]->setStyleSheet("border-image: url(:/38shenshengye.png);"); isWall[3][9][9]=38;
    table[3][9][10]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][9][10]=5;
    table[3][9][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][9][11]=0;
    table[3][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][9][12]=0;
    table[3][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][10][0]=0;
    table[3][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][10][1]=0;
    table[3][10][2]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][10][2]=6;
    table[3][10][3]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][10][3]=6;
    table[3][10][4]->setStyleSheet("border-image: url(:/6defence.png);"); isWall[3][10][4]=6;
    table[3][10][5]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[3][10][5]=3;
    table[3][10][6]->setStyleSheet("border-image: url(:/37yinggang.png);"); isWall[3][10][6]=37;
    table[3][10][7]->setStyleSheet("border-image: url(:/3reddoor.png);"); isWall[3][10][7]=3;
    table[3][10][8]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][10][8]=5;
    table[3][10][9]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][10][9]=5;
    table[3][10][10]->setStyleSheet("border-image: url(:/5attack.png);"); isWall[3][10][10]=5;
    table[3][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][10][11]=0;
    table[3][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][10][12]=0;
    table[3][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][11][0]=0;
    table[3][11][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][1]=0;
    table[3][11][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][2]=0;
    table[3][11][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][3]=0;
    table[3][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][4]=0;
    table[3][11][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][5]=0;
    table[3][11][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][6]=0;
    table[3][11][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][7]=0;
    table[3][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][8]=0;
    table[3][11][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][9]=0;
    table[3][11][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][10]=0;
    table[3][11][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[3][11][11]=0;
    table[3][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][11][12]=0;
    table[3][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][0]=0;
    table[3][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][1]=0;
    table[3][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][2]=0;
    table[3][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][3]=0;
    table[3][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][4]=0;
    table[3][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][5]=0;
    table[3][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][6]=0;
    table[3][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][7]=0;
    table[3][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][8]=0;
    table[3][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][9]=0;
    table[3][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][10]=0;
    table[3][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][11]=0;
    table[3][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[3][12][12]=0;
}
void MainWindow::settable5()
{
    table[4][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][0]=0;
    table[4][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][1]=0;
    table[4][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][2]=0;
    table[4][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][3]=0;
    table[4][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][4]=0;
    table[4][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][5]=0;
    table[4][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][6]=0;
    table[4][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][7]=0;
    table[4][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][8]=0;
    table[4][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][9]=0;
    table[4][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][10]=0;
    table[4][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][11]=0;
    table[4][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][0][12]=0;
    table[4][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][1][0]=0;
    table[4][1][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][1]=0;
    table[4][1][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][2]=0;
    table[4][1][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][3]=0;
    table[4][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][4]=0;
    table[4][1][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][5]=0;
    table[4][1][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][6]=0;
    table[4][1][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][7]=0;
    table[4][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][8]=0;
    table[4][1][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][9]=0;
    table[4][1][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][10]=0;
    table[4][1][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][1][11]=0;
    table[4][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][1][12]=0;
    table[4][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][2][0]=0;
    table[4][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][2][1]=0;
    table[4][2][2]->setStyleSheet("border-image: url(:/-5redkey.png);"); isWall[4][2][2]=-5;
    table[4][2][3]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][2][3]=26;
    table[4][2][4]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][2][4]=8;
    table[4][2][5]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][2][5]=8;
    table[4][2][6]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[4][2][6]=10;
    table[4][2][7]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][2][7]=8;
    table[4][2][8]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][2][8]=8;
    table[4][2][9]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][2][9]=26;
    table[4][2][10]->setStyleSheet("border-image: url(:/-5redkey.png);"); isWall[4][2][10]=-5;
    table[4][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][2][11]=0;
    table[4][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][2][12]=0;
    table[4][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][3][0]=0;
    table[4][3][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][3][1]=0;
    table[4][3][2]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][3][2]=26;
    table[4][3][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][3][3]=0;
    table[4][3][4]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][3][4]=25;
    table[4][3][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][3][5]=0;
    table[4][3][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][3][6]=-1;
    table[4][3][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][3][7]=0;
    table[4][3][8]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][3][8]=25;
    table[4][3][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][3][9]=0;
    table[4][3][10]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][3][10]=26;
    table[4][3][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][3][11]=0;
    table[4][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][3][12]=0;
    table[4][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][4][0]=0;
    table[4][4][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][4][1]=0;
    table[4][4][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][2]=-1;
    table[4][4][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][3]=-1;
    table[4][4][4]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][4][4]=8;
    table[4][4][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][5]=-1;
    table[4][4][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][6]=-1;
    table[4][4][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][7]=-1;
    table[4][4][8]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][4][8]=8;
    table[4][4][9]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][9]=-1;
    table[4][4][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][4][10]=-1;
    table[4][4][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][4][11]=0;
    table[4][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][4][12]=0;
    table[4][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][5][0]=0;
    table[4][5][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][5][1]=0;
    table[4][5][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][5][2]=-1;
    table[4][5][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][5][3]=0;
    table[4][5][4]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][5][4]=25;
    table[4][5][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][5][5]=0;
    table[4][5][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][5][6]=-1;
    table[4][5][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][5][7]=0;
    table[4][5][8]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][5][8]=25;
    table[4][5][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][5][9]=0;
    table[4][5][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][5][10]=-1;
    table[4][5][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][5][11]=0;
    table[4][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][5][12]=0;
    table[4][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][6][0]=0;
    table[4][6][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][6][1]=0;
    table[4][6][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][2]=-1;
    table[4][6][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][3]=-1;
    table[4][6][4]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][6][4]=8;
    table[4][6][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][5]=-1;
    table[4][6][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][6]=-1;
    table[4][6][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][7]=-1;
    table[4][6][8]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][6][8]=8;
    table[4][6][9]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][9]=-1;
    table[4][6][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][6][10]=-1;
    table[4][6][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][6][11]=0;
    table[4][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][6][12]=0;
    table[4][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][7][0]=0;
    table[4][7][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][7][1]=0;
    table[4][7][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][7][2]=-1;
    table[4][7][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][7][3]=0;
    table[4][7][4]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][7][4]=25;
    table[4][7][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][7][5]=0;
    table[4][7][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][7][6]=-1;
    table[4][7][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][7][7]=0;
    table[4][7][8]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][7][8]=25;
    table[4][7][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][7][9]=0;
    table[4][7][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][7][10]=-1;
    table[4][7][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][7][11]=0;
    table[4][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][7][12]=0;
    table[4][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][8][0]=0;
    table[4][8][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][8][1]=0;
    table[4][8][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][2]=-1;
    table[4][8][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][3]=-1;
    table[4][8][4]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][8][4]=8;
    table[4][8][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][5]=-1;
    table[4][8][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][6]=-1;
    table[4][8][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][7]=-1;
    table[4][8][8]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][8][8]=8;
    table[4][8][9]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][9]=-1;
    table[4][8][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][8][10]=-1;
    table[4][8][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][8][11]=0;
    table[4][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][8][12]=0;
    table[4][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][9][0]=0;
    table[4][9][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][9][1]=0;
    table[4][9][2]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][9][2]=26;
    table[4][9][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][9][3]=0;
    table[4][9][4]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][9][4]=25;
    table[4][9][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][9][5]=0;
    table[4][9][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[4][9][6]=-1;
    table[4][9][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][9][7]=0;
    table[4][9][8]->setStyleSheet("border-image: url(:/25monster.png);"); isWall[4][9][8]=25;
    table[4][9][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][9][9]=0;
    table[4][9][10]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][9][10]=26;
    table[4][9][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][9][11]=0;
    table[4][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][9][12]=0;
    table[4][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][10][0]=0;
    table[4][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][10][1]=0;
    table[4][10][2]->setStyleSheet("border-image: url(:/-5redkey.png);"); isWall[4][10][2]=-5;
    table[4][10][3]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][10][3]=26;
    table[4][10][4]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][10][4]=8;
    table[4][10][5]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][10][5]=8;
    table[4][10][6]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[4][10][6]=11;
    table[4][10][7]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][10][7]=8;
    table[4][10][8]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[4][10][8]=8;
    table[4][10][9]->setStyleSheet("border-image: url(:/26monster.png);"); isWall[4][10][9]=26;
    table[4][10][10]->setStyleSheet("border-image: url(:/-5redkey.png);"); isWall[4][10][10]=-5;
    table[4][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][10][11]=0;
    table[4][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][10][12]=0;
    table[4][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][11][0]=0;
    table[4][11][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][1]=0;
    table[4][11][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][2]=0;
    table[4][11][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][3]=0;
    table[4][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][4]=0;
    table[4][11][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][5]=0;
    table[4][11][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][6]=0;
    table[4][11][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][7]=0;
    table[4][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][8]=0;
    table[4][11][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][9]=0;
    table[4][11][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][10]=0;
    table[4][11][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[4][11][11]=0;
    table[4][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][11][12]=0;
    table[4][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][0]=0;
    table[4][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][1]=0;
    table[4][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][2]=0;
    table[4][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][3]=0;
    table[4][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][4]=0;
    table[4][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][5]=0;
    table[4][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][6]=0;
    table[4][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][7]=0;
    table[4][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][8]=0;
    table[4][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][9]=0;
    table[4][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][10]=0;
    table[4][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][11]=0;
    table[4][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[4][12][12]=0;
}
void MainWindow::settable6()
{
    table[5][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][0]=0;
    table[5][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][1]=0;
    table[5][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][2]=0;
    table[5][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][3]=0;
    table[5][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][4]=0;
    table[5][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][5]=0;
    table[5][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][6]=0;
    table[5][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][7]=0;
    table[5][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][8]=0;
    table[5][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][9]=0;
    table[5][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][10]=0;
    table[5][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][11]=0;
    table[5][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][0][12]=0;
    table[5][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][1][0]=0;
    table[5][1][1]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][1][1]=-8;
    table[5][1][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][1][2]=-8;
    table[5][1][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][1][3]=-8;
    table[5][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][1][4]=0;
    table[5][1][5]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][1][5]=28;
    table[5][1][6]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[5][1][6]=10;
    table[5][1][7]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][1][7]=28;
    table[5][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][1][8]=0;
    table[5][1][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][1][9]=-9;
    table[5][1][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][1][10]=-9;
    table[5][1][11]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][1][11]=-9;
    table[5][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][1][12]=0;
    table[5][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][2][0]=0;
    table[5][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][2][1]=0;
    table[5][2][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][2][2]=0;
    table[5][2][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][2][3]=-8;
    table[5][2][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][2][4]=0;
    table[5][2][5]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][2][5]=-9;
    table[5][2][6]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][2][6]=28;
    table[5][2][7]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][2][7]=-9;
    table[5][2][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][2][8]=0;
    table[5][2][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][2][9]=-9;
    table[5][2][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][2][10]=0;
    table[5][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][2][11]=0;
    table[5][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][2][12]=0;
    table[5][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][3][0]=0;
    table[5][3][1]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][3][1]=-8;
    table[5][3][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][3][2]=-8;
    table[5][3][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][3][3]=-8;
    table[5][3][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][3][4]=0;
    table[5][3][5]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][3][5]=28;
    table[5][3][6]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][3][6]=-8;
    table[5][3][7]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][3][7]=28;
    table[5][3][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][3][8]=0;
    table[5][3][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][3][9]=-9;
    table[5][3][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][3][10]=-9;
    table[5][3][11]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][3][11]=-9;
    table[5][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][3][12]=0;
    table[5][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][4][0]=0;
    table[5][4][1]->setStyleSheet("border-image: url(:/1yellowdoor.png);"); isWall[5][4][1]=1;
    table[5][4][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][2]=0;
    table[5][4][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][3]=0;
    table[5][4][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][4]=0;
    table[5][4][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][5]=0;
    table[5][4][6]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][4][6]=29;
    table[5][4][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][7]=0;
    table[5][4][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][8]=0;
    table[5][4][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][9]=0;
    table[5][4][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][4][10]=0;
    table[5][4][11]->setStyleSheet("border-image: url(:/1yellowdoor.png);"); isWall[5][4][11]=1;
    table[5][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][4][12]=0;
    table[5][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][5][0]=0;
    table[5][5][1]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][5][1]=29;
    table[5][5][2]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][5][2]=28;
    table[5][5][3]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][5][3]=29;
    table[5][5][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][5][4]=0;
    table[5][5][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][5][5]=-1;
    table[5][5][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][5][6]=-1;
    table[5][5][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][5][7]=-1;
    table[5][5][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][5][8]=0;
    table[5][5][9]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][5][9]=29;
    table[5][5][10]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][5][10]=28;
    table[5][5][11]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][5][11]=29;
    table[5][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][5][12]=0;
    table[5][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][6][0]=0;
    table[5][6][1]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][6][1]=-8;
    table[5][6][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][6][2]=-8;
    table[5][6][3]->setStyleSheet("border-image: url(:/27monster.png);"); isWall[5][6][3]=27;
    table[5][6][4]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[5][6][4]=9;
    table[5][6][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][6][5]=-1;
    table[5][6][6]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[5][6][6]=30;
    table[5][6][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][6][7]=-1;
    table[5][6][8]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[5][6][8]=9;
    table[5][6][9]->setStyleSheet("border-image: url(:/27monster.png);"); isWall[5][6][9]=27;
    table[5][6][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][6][10]=-9;
    table[5][6][11]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][6][11]=-9;
    table[5][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][6][12]=0;
    table[5][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][7][0]=0;
    table[5][7][1]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][7][1]=29;
    table[5][7][2]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][7][2]=28;
    table[5][7][3]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][7][3]=29;
    table[5][7][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][7][4]=0;
    table[5][7][5]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][7][5]=-1;
    table[5][7][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][7][6]=-1;
    table[5][7][7]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][7][7]=-1;
    table[5][7][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][7][8]=0;
    table[5][7][9]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][7][9]=29;
    table[5][7][10]->setStyleSheet("border-image: url(:/28monster.png);"); isWall[5][7][10]=28;
    table[5][7][11]->setStyleSheet("border-image: url(:/29monster.png);"); isWall[5][7][11]=29;
    table[5][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][7][12]=0;
    table[5][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][8][0]=0;
    table[5][8][1]->setStyleSheet("border-image: url(:/1yellowdoor.png);"); isWall[5][8][1]=1;
    table[5][8][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][2]=0;
    table[5][8][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][3]=0;
    table[5][8][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][4]=0;
    table[5][8][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][5]=0;
    table[5][8][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][8][6]=-1;
    table[5][8][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][7]=0;
    table[5][8][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][8]=0;
    table[5][8][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][9]=0;
    table[5][8][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][8][10]=0;
    table[5][8][11]->setStyleSheet("border-image: url(:/1yellowdoor.png);"); isWall[5][8][11]=1;
    table[5][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][8][12]=0;
    table[5][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][9][0]=0;
    table[5][9][1]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][9][1]=-8;
    table[5][9][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][9][2]=-8;
    table[5][9][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][9][3]=-8;
    table[5][9][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][9][4]=0;
    table[5][9][5]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][9][5]=8;
    table[5][9][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][9][6]=8;
    table[5][9][7]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][9][7]=8;
    table[5][9][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][9][8]=0;
    table[5][9][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][9][9]=-9;
    table[5][9][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][9][10]=-9;
    table[5][9][11]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][9][11]=-9;
    table[5][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][9][12]=0;
    table[5][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][10][0]=0;
    table[5][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][10][1]=0;
    table[5][10][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][10][2]=0;
    table[5][10][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][10][3]=-8;
    table[5][10][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][10][4]=0;
    table[5][10][5]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][10][5]=8;
    table[5][10][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[5][10][6]=-1;
    table[5][10][7]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][10][7]=8;
    table[5][10][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][10][8]=0;
    table[5][10][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][10][9]=-9;
    table[5][10][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][10][10]=0;
    table[5][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][10][11]=0;
    table[5][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][10][12]=0;
    table[5][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][11][0]=0;
    table[5][11][1]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][11][1]=-8;
    table[5][11][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][11][2]=-8;
    table[5][11][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[5][11][3]=-8;
    table[5][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][11][4]=0;
    table[5][11][5]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][11][5]=8;
    table[5][11][6]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[5][11][6]=11;
    table[5][11][7]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[5][11][7]=8;
    table[5][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[5][11][8]=0;
    table[5][11][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][11][9]=-9;
    table[5][11][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][11][10]=-9;
    table[5][11][11]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[5][11][11]=-9;
    table[5][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][11][12]=0;
    table[5][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][0]=0;
    table[5][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][1]=0;
    table[5][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][2]=0;
    table[5][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][3]=0;
    table[5][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][4]=0;
    table[5][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][5]=0;
    table[5][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][6]=0;
    table[5][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][7]=0;
    table[5][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][8]=0;
    table[5][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][9]=0;
    table[5][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][10]=0;
    table[5][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][11]=0;
    table[5][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[5][12][12]=0;
}
void MainWindow::settable7()
{
    table[6][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][0]=0;
    table[6][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][1]=0;
    table[6][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][2]=0;
    table[6][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][3]=0;
    table[6][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][4]=0;
    table[6][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][5]=0;
    table[6][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][6]=0;
    table[6][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][7]=0;
    table[6][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][8]=0;
    table[6][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][9]=0;
    table[6][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][10]=0;
    table[6][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][11]=0;
    table[6][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][0][12]=0;
    table[6][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][1][0]=0;
    table[6][1][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][1]=0;
    table[6][1][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][2]=0;
    table[6][1][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][3]=0;
    table[6][1][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][4]=0;
    table[6][1][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][5]=0;
    table[6][1][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][6]=0;
    table[6][1][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][7]=0;
    table[6][1][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][8]=0;
    table[6][1][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][9]=0;
    table[6][1][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][10]=0;
    table[6][1][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][1][11]=0;
    table[6][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][1][12]=0;
    table[6][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][2][0]=0;
    table[6][2][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][2][1]=0;
    table[6][2][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][2][2]=-8;
    table[6][2][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][2][3]=-8;
    table[6][2][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][2][4]=-8;
    table[6][2][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][2][5]=0;
    table[6][2][6]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[6][2][6]=10;
    table[6][2][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][2][7]=0;
    table[6][2][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][2][8]=-9;
    table[6][2][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][2][9]=-9;
    table[6][2][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][2][10]=-9;
    table[6][2][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][2][11]=0;
    table[6][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][2][12]=0;
    table[6][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][3][0]=0;
    table[6][3][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][3][1]=0;
    table[6][3][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][3][2]=-8;
    table[6][3][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][3][3]=-8;
    table[6][3][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][3][4]=-8;
    table[6][3][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][3][5]=0;
    table[6][3][6]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[6][3][6]=-2;
    table[6][3][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][3][7]=0;
    table[6][3][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][3][8]=-9;
    table[6][3][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][3][9]=-9;
    table[6][3][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][3][10]=-9;
    table[6][3][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][3][11]=0;
    table[6][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][3][12]=0;
    table[6][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][4][0]=0;
    table[6][4][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][4][1]=0;
    table[6][4][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][4][2]=-8;
    table[6][4][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][4][3]=-8;
    table[6][4][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][4][4]=-8;
    table[6][4][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][4][5]=0;
    table[6][4][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[6][4][6]=8;
    table[6][4][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][4][7]=0;
    table[6][4][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][4][8]=-9;
    table[6][4][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][4][9]=-9;
    table[6][4][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][4][10]=-9;
    table[6][4][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][4][11]=0;
    table[6][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][4][12]=0;
    table[6][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][5][0]=0;
    table[6][5][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][5][1]=0;
    table[6][5][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][5][2]=-8;
    table[6][5][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][5][3]=-8;
    table[6][5][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][5][4]=-8;
    table[6][5][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][5][5]=0;
    table[6][5][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[6][5][6]=8;
    table[6][5][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][5][7]=0;
    table[6][5][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][5][8]=-9;
    table[6][5][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][5][9]=-9;
    table[6][5][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][5][10]=-9;
    table[6][5][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][5][11]=0;
    table[6][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][5][12]=0;
    table[6][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][6][0]=0;
    table[6][6][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][6][1]=0;
    table[6][6][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][6][2]=-8;
    table[6][6][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][6][3]=-8;
    table[6][6][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][6][4]=-8;
    table[6][6][5]->setStyleSheet("border-image: url(:/31monster.png);"); isWall[6][6][5]=31;
    table[6][6][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[6][6][6]=8;
    table[6][6][7]->setStyleSheet("border-image: url(:/32monster.png);"); isWall[6][6][7]=32;
    table[6][6][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][6][8]=-9;
    table[6][6][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][6][9]=-9;
    table[6][6][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][6][10]=-9;
    table[6][6][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][6][11]=0;
    table[6][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][6][12]=0;
    table[6][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][7][0]=0;
    table[6][7][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][7][1]=0;
    table[6][7][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][7][2]=-8;
    table[6][7][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][7][3]=-8;
    table[6][7][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][7][4]=-8;
    table[6][7][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][7][5]=0;
    table[6][7][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[6][7][6]=8;
    table[6][7][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][7][7]=0;
    table[6][7][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][7][8]=-9;
    table[6][7][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][7][9]=-9;
    table[6][7][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][7][10]=-9;
    table[6][7][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][7][11]=0;
    table[6][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][7][12]=0;
    table[6][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][8][0]=0;
    table[6][8][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][8][1]=0;
    table[6][8][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][8][2]=-8;
    table[6][8][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][8][3]=-8;
    table[6][8][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][8][4]=-8;
    table[6][8][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][8][5]=0;
    table[6][8][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[6][8][6]=8;
    table[6][8][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][8][7]=0;
    table[6][8][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][8][8]=-9;
    table[6][8][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][8][9]=-9;
    table[6][8][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][8][10]=-9;
    table[6][8][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][8][11]=0;
    table[6][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][8][12]=0;
    table[6][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][9][0]=0;
    table[6][9][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][9][1]=0;
    table[6][9][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][9][2]=-8;
    table[6][9][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][9][3]=-8;
    table[6][9][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][9][4]=-8;
    table[6][9][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][9][5]=0;
    table[6][9][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[6][9][6]=-1;
    table[6][9][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][9][7]=0;
    table[6][9][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][9][8]=-9;
    table[6][9][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][9][9]=-9;
    table[6][9][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][9][10]=-9;
    table[6][9][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][9][11]=0;
    table[6][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][9][12]=0;
    table[6][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][10][0]=0;
    table[6][10][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][10][1]=0;
    table[6][10][2]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][10][2]=-8;
    table[6][10][3]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][10][3]=-8;
    table[6][10][4]->setStyleSheet("border-image: url(:/-8bigattack.png);"); isWall[6][10][4]=-8;
    table[6][10][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][10][5]=0;
    table[6][10][6]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[6][10][6]=11;
    table[6][10][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][10][7]=0;
    table[6][10][8]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][10][8]=-9;
    table[6][10][9]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][10][9]=-9;
    table[6][10][10]->setStyleSheet("border-image: url(:/-9bigdefence.png);"); isWall[6][10][10]=-9;
    table[6][10][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][10][11]=0;
    table[6][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][10][12]=0;
    table[6][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][11][0]=0;
    table[6][11][1]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][1]=0;
    table[6][11][2]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][2]=0;
    table[6][11][3]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][3]=0;
    table[6][11][4]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][4]=0;
    table[6][11][5]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][5]=0;
    table[6][11][6]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][6]=0;
    table[6][11][7]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][7]=0;
    table[6][11][8]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][8]=0;
    table[6][11][9]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][9]=0;
    table[6][11][10]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][10]=0;
    table[6][11][11]->setStyleSheet("border-image: url(:/wall.png);"); isWall[6][11][11]=0;
    table[6][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][11][12]=0;
    table[6][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][0]=0;
    table[6][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][1]=0;
    table[6][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][2]=0;
    table[6][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][3]=0;
    table[6][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][4]=0;
    table[6][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][5]=0;
    table[6][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][6]=0;
    table[6][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][7]=0;
    table[6][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][8]=0;
    table[6][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][9]=0;
    table[6][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][10]=0;
    table[6][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][11]=0;
    table[6][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[6][12][12]=0;
}
void MainWindow::settable8()
{
    table[7][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][0]=0;
    table[7][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][1]=0;
    table[7][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][2]=0;
    table[7][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][3]=0;
    table[7][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][4]=0;
    table[7][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][5]=0;
    table[7][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][6]=0;
    table[7][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][7]=0;
    table[7][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][8]=0;
    table[7][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][9]=0;
    table[7][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][10]=0;
    table[7][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][11]=0;
    table[7][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][0][12]=0;
    table[7][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][0]=0;
    table[7][1][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][1]=0;
    table[7][1][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][2]=0;
    table[7][1][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][3]=0;
    table[7][1][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][4]=0;
    table[7][1][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][5]=0;
    table[7][1][6]->setStyleSheet("border-image: url(:/10upstair.png);"); isWall[7][1][6]=10;
    table[7][1][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][7]=0;
    table[7][1][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][8]=0;
    table[7][1][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][9]=0;
    table[7][1][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][10]=0;
    table[7][1][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][11]=0;
    table[7][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][1][12]=0;
    table[7][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][2][0]=0;
    table[7][2][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][2][1]=0;
    table[7][2][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][2][2]=-1;
    table[7][2][3]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[7][2][3]=-2;
    table[7][2][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][2][4]=-1;
    table[7][2][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][2][5]=0;
    table[7][2][6]->setStyleSheet("border-image: url(:/34monster.png);"); isWall[7][2][6]=34;
    table[7][2][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][2][7]=0;
    table[7][2][8]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][2][8]=-1;
    table[7][2][9]->setStyleSheet("border-image: url(:/NPC1.png);"); isWall[7][2][9]=-2;
    table[7][2][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][2][10]=-1;
    table[7][2][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][2][11]=0;
    table[7][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][2][12]=0;
    table[7][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][3][0]=0;
    table[7][3][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][3][1]=0;
    table[7][3][2]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][3][2]=-1;
    table[7][3][3]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][3][3]=-1;
    table[7][3][4]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][3][4]=-1;
    table[7][3][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][3][5]=0;
    table[7][3][6]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][3][6]=30;
    table[7][3][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][3][7]=0;
    table[7][3][8]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][3][8]=-1;
    table[7][3][9]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][3][9]=-1;
    table[7][3][10]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][3][10]=-1;
    table[7][3][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][3][11]=0;
    table[7][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][3][12]=0;
    table[7][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][0]=0;
    table[7][4][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][1]=0;
    table[7][4][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][2]=0;
    table[7][4][3]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][4][3]=33;
    table[7][4][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][4]=0;
    table[7][4][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][5]=0;
    table[7][4][6]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][4][6]=30;
    table[7][4][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][7]=0;
    table[7][4][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][8]=0;
    table[7][4][9]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][4][9]=30;
    table[7][4][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][10]=0;
    table[7][4][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][11]=0;
    table[7][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][4][12]=0;
    table[7][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][5][0]=0;
    table[7][5][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][5][1]=0;
    table[7][5][2]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][5][2]=33;
    table[7][5][3]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][5][3]=33;
    table[7][5][4]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][5][4]=33;
    table[7][5][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][5][5]=0;
    table[7][5][6]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][5][6]=30;
    table[7][5][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][5][7]=0;
    table[7][5][8]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][5][8]=30;
    table[7][5][9]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][5][9]=30;
    table[7][5][10]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][5][10]=30;
    table[7][5][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][5][11]=0;
    table[7][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][5][12]=0;
    table[7][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][6][0]=0;
    table[7][6][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][6][1]=0;
    table[7][6][2]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][6][2]=33;
    table[7][6][3]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][6][3]=33;
    table[7][6][4]->setStyleSheet("border-image: url(:/33monster.png);"); isWall[7][6][4]=33;
    table[7][6][5]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[7][6][5]=9;
    table[7][6][6]->setStyleSheet("border-image: url(:/14monster.png);"); isWall[7][6][6]=14;
    table[7][6][7]->setStyleSheet("border-image: url(:/9flowerdoor.png);"); isWall[7][6][7]=9;
    table[7][6][8]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][6][8]=30;
    table[7][6][9]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][6][9]=30;
    table[7][6][10]->setStyleSheet("border-image: url(:/30monster.png);"); isWall[7][6][10]=30;
    table[7][6][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][6][11]=0;
    table[7][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][6][12]=0;
    table[7][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][0]=0;
    table[7][7][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][1]=0;
    table[7][7][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][2]=0;
    table[7][7][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][3]=0;
    table[7][7][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][4]=0;
    table[7][7][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][5]=0;
    table[7][7][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[7][7][6]=8;
    table[7][7][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][7]=0;
    table[7][7][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][8]=0;
    table[7][7][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][9]=0;
    table[7][7][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][10]=0;
    table[7][7][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][11]=0;
    table[7][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][7][12]=0;
    table[7][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][0]=0;
    table[7][8][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][1]=0;
    table[7][8][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][2]=0;
    table[7][8][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][3]=0;
    table[7][8][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][4]=0;
    table[7][8][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][5]=0;
    table[7][8][6]->setStyleSheet("border-image: url(:/8greenbottle.png);"); isWall[7][8][6]=8;
    table[7][8][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][7]=0;
    table[7][8][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][8]=0;
    table[7][8][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][9]=0;
    table[7][8][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][10]=0;
    table[7][8][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][11]=0;
    table[7][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][8][12]=0;
    table[7][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][0]=0;
    table[7][9][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][1]=0;
    table[7][9][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][2]=0;
    table[7][9][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][3]=0;
    table[7][9][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][4]=0;
    table[7][9][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][5]=0;
    table[7][9][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[7][9][6]=-1;
    table[7][9][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][7]=0;
    table[7][9][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][8]=0;
    table[7][9][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][9]=0;
    table[7][9][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][10]=0;
    table[7][9][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][11]=0;
    table[7][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][9][12]=0;
    table[7][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][0]=0;
    table[7][10][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][1]=0;
    table[7][10][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][2]=0;
    table[7][10][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][3]=0;
    table[7][10][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][4]=0;
    table[7][10][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][5]=0;
    table[7][10][6]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[7][10][6]=11;
    table[7][10][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][7]=0;
    table[7][10][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][8]=0;
    table[7][10][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][9]=0;
    table[7][10][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][10]=0;
    table[7][10][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][11]=0;
    table[7][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][10][12]=0;
    table[7][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][0]=0;
    table[7][11][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][1]=0;
    table[7][11][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][2]=0;
    table[7][11][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][3]=0;
    table[7][11][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][4]=0;
    table[7][11][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][5]=0;
    table[7][11][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][6]=0;
    table[7][11][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][7]=0;
    table[7][11][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][8]=0;
    table[7][11][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][9]=0;
    table[7][11][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][10]=0;
    table[7][11][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][11]=0;
    table[7][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][11][12]=0;
    table[7][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][0]=0;
    table[7][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][1]=0;
    table[7][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][2]=0;
    table[7][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][3]=0;
    table[7][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][4]=0;
    table[7][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][5]=0;
    table[7][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][6]=0;
    table[7][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][7]=0;
    table[7][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][8]=0;
    table[7][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][9]=0;
    table[7][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][10]=0;
    table[7][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][11]=0;
    table[7][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[7][12][12]=0;
}
void MainWindow::settable9()
{
    table[8][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][0]=0;
    table[8][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][1]=0;
    table[8][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][2]=0;
    table[8][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][3]=0;
    table[8][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][4]=0;
    table[8][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][5]=0;
    table[8][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][6]=0;
    table[8][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][7]=0;
    table[8][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][8]=0;
    table[8][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][9]=0;
    table[8][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][10]=0;
    table[8][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][11]=0;
    table[8][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][0][12]=0;
    table[8][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][0]=0;
    table[8][1][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][1]=0;
    table[8][1][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][2]=0;
    table[8][1][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][3]=0;
    table[8][1][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][4]=0;
    table[8][1][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][5]=0;
    table[8][1][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][6]=0;
    table[8][1][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][7]=0;
    table[8][1][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][8]=0;
    table[8][1][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][9]=0;
    table[8][1][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][10]=0;
    table[8][1][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][11]=0;
    table[8][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][1][12]=0;
    table[8][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][0]=0;
    table[8][2][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][1]=0;
    table[8][2][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][2]=0;
    table[8][2][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][3]=0;
    table[8][2][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][4]=0;
    table[8][2][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][5]=0;
    table[8][2][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][6]=0;
    table[8][2][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][7]=0;
    table[8][2][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][8]=0;
    table[8][2][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][9]=0;
    table[8][2][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][10]=0;
    table[8][2][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][11]=0;
    table[8][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][2][12]=0;
    table[8][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][0]=0;
    table[8][3][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][1]=0;
    table[8][3][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][2]=0;
    table[8][3][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][3]=0;
    table[8][3][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][4]=0;
    table[8][3][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][5]=0;
    table[8][3][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][6]=0;
    table[8][3][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][7]=0;
    table[8][3][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][8]=0;
    table[8][3][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][9]=0;
    table[8][3][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][10]=0;
    table[8][3][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][11]=0;
    table[8][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][3][12]=0;
    table[8][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][0]=0;
    table[8][4][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][1]=0;
    table[8][4][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][2]=0;
    table[8][4][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][3]=0;
    table[8][4][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][4]=0;
    table[8][4][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][5]=0;
    table[8][4][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][6]=0;
    table[8][4][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][7]=0;
    table[8][4][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][8]=0;
    table[8][4][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][9]=0;
    table[8][4][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][10]=0;
    table[8][4][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][11]=0;
    table[8][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][4][12]=0;
    table[8][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][0]=0;
    table[8][5][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][1]=0;
    table[8][5][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][2]=0;
    table[8][5][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][3]=0;
    table[8][5][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][4]=0;
    table[8][5][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][5]=0;
    table[8][5][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][6]=0;
    table[8][5][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][7]=0;
    table[8][5][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][8]=0;
    table[8][5][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][9]=0;
    table[8][5][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][10]=0;
    table[8][5][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][11]=0;
    table[8][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][5][12]=0;
    table[8][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][0]=0;
    table[8][6][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][1]=0;
    table[8][6][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][2]=0;
    table[8][6][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][3]=0;
    table[8][6][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][4]=0;
    table[8][6][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][5]=0;
    table[8][6][6]->setStyleSheet("border-image: url(:/35monster.png);"); isWall[8][6][6]=35;
    table[8][6][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][7]=0;
    table[8][6][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][8]=0;
    table[8][6][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][9]=0;
    table[8][6][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][10]=0;
    table[8][6][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][11]=0;
    table[8][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][6][12]=0;
    table[8][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][0]=0;
    table[8][7][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][1]=0;
    table[8][7][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][2]=0;
    table[8][7][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][3]=0;
    table[8][7][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][4]=0;
    table[8][7][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][5]=0;
    table[8][7][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[8][7][6]=-1;
    table[8][7][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][7]=0;
    table[8][7][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][8]=0;
    table[8][7][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][9]=0;
    table[8][7][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][10]=0;
    table[8][7][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][11]=0;
    table[8][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][7][12]=0;
    table[8][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][0]=0;
    table[8][8][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][1]=0;
    table[8][8][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][2]=0;
    table[8][8][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][3]=0;
    table[8][8][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][4]=0;
    table[8][8][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][5]=0;
    table[8][8][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[8][8][6]=-1;
    table[8][8][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][7]=0;
    table[8][8][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][8]=0;
    table[8][8][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][9]=0;
    table[8][8][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][10]=0;
    table[8][8][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][11]=0;
    table[8][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][8][12]=0;
    table[8][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][0]=0;
    table[8][9][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][1]=0;
    table[8][9][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][2]=0;
    table[8][9][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][3]=0;
    table[8][9][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][4]=0;
    table[8][9][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][5]=0;
    table[8][9][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[8][9][6]=-1;
    table[8][9][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][7]=0;
    table[8][9][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][8]=0;
    table[8][9][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][9]=0;
    table[8][9][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][10]=0;
    table[8][9][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][11]=0;
    table[8][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][9][12]=0;
    table[8][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][0]=0;
    table[8][10][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][1]=0;
    table[8][10][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][2]=0;
    table[8][10][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][3]=0;
    table[8][10][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][4]=0;
    table[8][10][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][5]=0;
    table[8][10][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[8][10][6]=-1;
    table[8][10][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][7]=0;
    table[8][10][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][8]=0;
    table[8][10][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][9]=0;
    table[8][10][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][10]=0;
    table[8][10][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][11]=0;
    table[8][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][10][12]=0;
    table[8][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][0]=0;
    table[8][11][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][1]=0;
    table[8][11][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][2]=0;
    table[8][11][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][3]=0;
    table[8][11][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][4]=0;
    table[8][11][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][5]=0;
    table[8][11][6]->setStyleSheet("border-image: url(:/11downstair.png);"); isWall[8][11][6]=11;
    table[8][11][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][7]=0;
    table[8][11][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][8]=0;
    table[8][11][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][9]=0;
    table[8][11][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][10]=0;
    table[8][11][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][11]=0;
    table[8][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][11][12]=0;
    table[8][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][0]=0;
    table[8][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][1]=0;
    table[8][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][2]=0;
    table[8][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][3]=0;
    table[8][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][4]=0;
    table[8][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][5]=0;
    table[8][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][6]=0;
    table[8][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][7]=0;
    table[8][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][8]=0;
    table[8][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][9]=0;
    table[8][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][10]=0;
    table[8][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][11]=0;
    table[8][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[8][12][12]=0;
}
void MainWindow::settable10()
{
    table[9][0][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][0]=0;
    table[9][0][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][1]=0;
    table[9][0][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][2]=0;
    table[9][0][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][3]=0;
    table[9][0][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][4]=0;
    table[9][0][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][5]=0;
    table[9][0][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][6]=0;
    table[9][0][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][7]=0;
    table[9][0][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][8]=0;
    table[9][0][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][9]=0;
    table[9][0][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][10]=0;
    table[9][0][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][11]=0;
    table[9][0][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][0][12]=0;
    table[9][1][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][0]=0;
    table[9][1][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][1]=0;
    table[9][1][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][2]=0;
    table[9][1][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][3]=0;
    table[9][1][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][4]=0;
    table[9][1][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][5]=0;
    table[9][1][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][6]=0;
    table[9][1][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][7]=0;
    table[9][1][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][8]=0;
    table[9][1][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][9]=0;
    table[9][1][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][10]=0;
    table[9][1][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][11]=0;
    table[9][1][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][1][12]=0;
    table[9][2][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][0]=0;
    table[9][2][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][1]=0;
    table[9][2][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][2]=0;
    table[9][2][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][3]=0;
    table[9][2][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][4]=0;
    table[9][2][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][5]=0;
    table[9][2][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][6]=0;
    table[9][2][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][7]=0;
    table[9][2][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][8]=0;
    table[9][2][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][9]=0;
    table[9][2][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][10]=0;
    table[9][2][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][11]=0;
    table[9][2][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][2][12]=0;
    table[9][3][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][0]=0;
    table[9][3][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][1]=0;
    table[9][3][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][2]=0;
    table[9][3][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][3]=0;
    table[9][3][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][4]=0;
    table[9][3][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][5]=0;
    table[9][3][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][6]=0;
    table[9][3][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][7]=0;
    table[9][3][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][8]=0;
    table[9][3][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][9]=0;
    table[9][3][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][10]=0;
    table[9][3][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][11]=0;
    table[9][3][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][3][12]=0;
    table[9][4][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][0]=0;
    table[9][4][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][1]=0;
    table[9][4][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][2]=0;
    table[9][4][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][3]=0;
    table[9][4][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][4]=0;
    table[9][4][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][5]=0;
    table[9][4][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][6]=0;
    table[9][4][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][7]=0;
    table[9][4][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][8]=0;
    table[9][4][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][9]=0;
    table[9][4][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][10]=0;
    table[9][4][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][11]=0;
    table[9][4][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][4][12]=0;
    table[9][5][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][0]=0;
    table[9][5][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][1]=0;
    table[9][5][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][2]=0;
    table[9][5][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][3]=0;
    table[9][5][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][4]=0;
    table[9][5][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][5]=0;
    table[9][5][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][6]=0;
    table[9][5][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][7]=0;
    table[9][5][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][8]=0;
    table[9][5][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][9]=0;
    table[9][5][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][10]=0;
    table[9][5][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][11]=0;
    table[9][5][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][5][12]=0;
    table[9][6][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][0]=0;
    table[9][6][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][1]=0;
    table[9][6][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][2]=0;
    table[9][6][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][3]=0;
    table[9][6][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][4]=0;
    table[9][6][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][5]=0;
    table[9][6][6]->setStyleSheet("border-image: url(:/floor.png);"); isWall[9][6][6]=-1;
    table[9][6][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][7]=0;
    table[9][6][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][8]=0;
    table[9][6][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][9]=0;
    table[9][6][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][10]=0;
    table[9][6][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][11]=0;
    table[9][6][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][6][12]=0;
    table[9][7][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][0]=0;
    table[9][7][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][1]=0;
    table[9][7][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][2]=0;
    table[9][7][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][3]=0;
    table[9][7][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][4]=0;
    table[9][7][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][5]=0;
    table[9][7][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][6]=0;
    table[9][7][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][7]=0;
    table[9][7][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][8]=0;
    table[9][7][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][9]=0;
    table[9][7][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][10]=0;
    table[9][7][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][11]=0;
    table[9][7][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][7][12]=0;
    table[9][8][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][0]=0;
    table[9][8][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][1]=0;
    table[9][8][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][2]=0;
    table[9][8][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][3]=0;
    table[9][8][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][4]=0;
    table[9][8][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][5]=0;
    table[9][8][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][6]=0;
    table[9][8][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][7]=0;
    table[9][8][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][8]=0;
    table[9][8][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][9]=0;
    table[9][8][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][10]=0;
    table[9][8][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][11]=0;
    table[9][8][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][8][12]=0;
    table[9][9][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][0]=0;
    table[9][9][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][1]=0;
    table[9][9][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][2]=0;
    table[9][9][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][3]=0;
    table[9][9][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][4]=0;
    table[9][9][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][5]=0;
    table[9][9][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][6]=0;
    table[9][9][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][7]=0;
    table[9][9][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][8]=0;
    table[9][9][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][9]=0;
    table[9][9][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][10]=0;
    table[9][9][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][11]=0;
    table[9][9][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][9][12]=0;
    table[9][10][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][0]=0;
    table[9][10][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][1]=0;
    table[9][10][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][2]=0;
    table[9][10][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][3]=0;
    table[9][10][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][4]=0;
    table[9][10][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][5]=0;
    table[9][10][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][6]=0;
    table[9][10][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][7]=0;
    table[9][10][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][8]=0;
    table[9][10][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][9]=0;
    table[9][10][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][10]=0;
    table[9][10][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][11]=0;
    table[9][10][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][10][12]=0;
    table[9][11][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][0]=0;
    table[9][11][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][1]=0;
    table[9][11][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][2]=0;
    table[9][11][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][3]=0;
    table[9][11][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][4]=0;
    table[9][11][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][5]=0;
    table[9][11][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][6]=0;
    table[9][11][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][7]=0;
    table[9][11][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][8]=0;
    table[9][11][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][9]=0;
    table[9][11][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][10]=0;
    table[9][11][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][11]=0;
    table[9][11][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][11][12]=0;
    table[9][12][0]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][0]=0;
    table[9][12][1]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][1]=0;
    table[9][12][2]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][2]=0;
    table[9][12][3]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][3]=0;
    table[9][12][4]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][4]=0;
    table[9][12][5]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][5]=0;
    table[9][12][6]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][6]=0;
    table[9][12][7]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][7]=0;
    table[9][12][8]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][8]=0;
    table[9][12][9]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][9]=0;
    table[9][12][10]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][10]=0;
    table[9][12][11]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][11]=0;
    table[9][12][12]->setStyleSheet("border-image: url(:/star.png);"); isWall[9][12][12]=0;
}
void MainWindow::npcchoice00()
{
    if(goldnum>=50){
        goldnum=goldnum-50;statusnum[7]->display(goldnum);
        attacknum=attacknum+5;statusnum[3]->display(attacknum);
    }
}
void MainWindow::npcchoice01()
{
    if(goldnum>=50){
        goldnum=goldnum-50;statusnum[7]->display(goldnum);
        defencenum=defencenum+7;statusnum[4]->display(defencenum);
    }
}
void MainWindow::npcchoice02()
{
    if(goldnum>=50){
        goldnum=goldnum-50;statusnum[7]->display(goldnum);
        HPnum=HPnum+1000;statusnum[2]->display(HPnum);
    }
}
void MainWindow::npcchoice03()
{
    NPCtext[0]->hide();
    NPCchoice[0][0]->hide();
    NPCchoice[0][1]->hide();
    NPCchoice[0][2]->hide();
    NPCchoice[0][3]->hide();
}
void MainWindow::npcchoice10()
{
    attacknum=attacknum+5;statusnum[3]->display(attacknum);
    NPCtext[1]->hide();
    NPCchoice[1][0]->hide();
    NPCchoice[1][1]->hide();
    NPCchoice[1][2]->hide();
}
void MainWindow::npcchoice11()
{
    defencenum=defencenum+7;statusnum[4]->display(defencenum);
    NPCtext[1]->hide();
    NPCchoice[1][0]->hide();
    NPCchoice[1][1]->hide();
    NPCchoice[1][2]->hide();
}
void MainWindow::npcchoice12()
{
    HPnum=HPnum+1000;statusnum[2]->display(HPnum);
    NPCtext[1]->hide();
    NPCchoice[1][0]->hide();
    NPCchoice[1][1]->hide();
    NPCchoice[1][2]->hide();
}
void MainWindow::npcchoice20()
{
    if(goldnum>=50){
        goldnum=goldnum-50;statusnum[7]->display(goldnum);
        yellowkeynum=yellowkeynum+1;statusnum[8]->display(yellowkeynum);
    }
}
void MainWindow::npcchoice21()
{
    if(goldnum>=50){
        goldnum=goldnum-50;statusnum[7]->display(goldnum);
        bluekeynum=bluekeynum+1;statusnum[9]->display(bluekeynum);
    }
}
void MainWindow::npcchoice22()
{
    if(goldnum>=50){
        goldnum=goldnum-50;statusnum[7]->display(goldnum);
        redkeynum=redkeynum+1;statusnum[10]->display(redkeynum);
    }
}
void MainWindow::npcchoice23()
{
    NPCtext[2]->hide();
    NPCchoice[2][0]->hide();
    NPCchoice[2][1]->hide();
    NPCchoice[2][2]->hide();
    NPCchoice[2][3]->hide();
}
void MainWindow::npcchoice30()
{
    if(goldnum>=30){
        goldnum=goldnum-30;statusnum[7]->display(goldnum);
        magicdefencenum=magicdefencenum+5;statusnum[5]->display(magicdefencenum);
    }
}
void MainWindow::npcchoice31()
{
    NPCtext[3]->hide();
    NPCchoice[3][0]->hide();
    NPCchoice[3][1]->hide();
    NPCchoice[3][2]->hide();
    NPCchoice[3][3]->hide();
}
void MainWindow::npcchoice40()
{
    NPCtext[4]->hide();
    NPCchoice[4][0]->hide();
    NPCchoice[4][1]->hide();
    NPCchoice[4][2]->hide();
    NPCchoice[4][3]->hide();
}
