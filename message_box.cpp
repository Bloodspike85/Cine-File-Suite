#include "message_box.h"

Message_Box::Message_Box(QString Title,QString Text,int Taille_Text,int Bouton_ON_OFF):QWidget()
{
    initialisation_a_null();
    Layout = new QVBoxLayout(this);

    setWindowTitle(Title);
    text = new QLabel;
    Secondtext = new QLabel;
    text->setText(Text);

    text->setAlignment(Qt::AlignCenter);

    Layout->addWidget(text);



    if(Bouton_ON_OFF == ON)
    {
        Bouton_OK = new QPushButton("OK",this);

        Bouton_OK->setCursor(Qt::PointingHandCursor);
        Bouton_OK->setFont(QFont("Comic Sans MS",Taille_Text,QFont::Bold));//Q en majuscule et t en minuscule//

        Layout->addWidget(Bouton_OK);

        QObject::connect(Bouton_OK,SIGNAL(clicked()),this,SLOT(close()));
    }

    setLayout(Layout);
}

Message_Box::~Message_Box()
{
    fprintf(stderr,"Suppression de Message box ... \n");
    if(Bouton_OK != nullptr)
    {
       delete Bouton_OK;
    }
    if(text != nullptr)
    {
       delete text;
    }
    if(Secondtext != nullptr)
    {
       delete Secondtext;
    }
    if(Layout != nullptr)
    {
       delete Layout;
    }


   fprintf(stderr,"Suppression de message box OK \n");
}

void Message_Box::SetText(QString NewText)
{
    delete text;
    text = new QLabel;
    text->setText(NewText);

    text->setAlignment(Qt::AlignCenter);
    Layout->addWidget(text);

    qApp->processEvents();


}
void Message_Box::SetSecondText(QString NewText)
{
    delete Secondtext;
    Secondtext = new QLabel;

    Secondtext->setText(NewText);

    qApp->processEvents();


}
void Message_Box::SetTitle(QString NewTitle)
{
    setWindowTitle(NewTitle);
}
