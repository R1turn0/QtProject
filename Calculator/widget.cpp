#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this -> setMaximumSize(240, 350);
    this -> setMinimumSize(240, 350);

    this -> setWindowTitle("你看不到我");

    QFont f("仿宋", 15);  // 字体对象
    ui -> mainLineEdit -> setFont(f);

    // 按钮上放图标
    //QIcon delImage(".\\Photo\\delImage.png");
    //ui -> delButton -> setIcon(delImage);

    // 改变按钮背景UI
    //ui -> equalButton -> setStyleSheet("background:blue");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_oneButton_clicked()
{
    expression += "1";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_twoButton_clicked()
{
    expression += "2";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_threeButton_clicked()
{
    expression += "3";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_fourButton_clicked()
{
    expression += "4";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_fiveButton_clicked()
{
    expression += "5";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_sixButton_clicked()
{
    expression += "6";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_sevenButton_clicked()
{
    expression += "7";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_eightButton_clicked()
{
    expression += "8";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_nineButton_clicked()
{
    expression += "9";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_zeroButton_clicked()
{
    expression += "0";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_leftButton_clicked()
{
    expression += "(";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_rightButton_clicked()
{
    expression += ")";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_addButton_clicked()
{
    expression += "+";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_subButton_clicked()
{
    expression += "-";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_mulButton_clicked()
{
    expression += "*";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_divButton_clicked()
{
    expression += "/";
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_clearButton_clicked()
{
    expression.clear();
    ui -> mainLineEdit -> clear();
}


void Widget::on_delButton_clicked()
{
    expression.chop(1);
    ui -> mainLineEdit -> setText(expression);
}


void Widget::on_equalButton_clicked()
{
    expression += "=";
    ui -> mainLineEdit -> setText(expression);

    QStack<double> s_num, s_opt;

    char opt[128] = {0};
    int i = 0, tmp = 0;
    double num1, num2;
    double num3;

    // 把QString转换成char*
    QByteArray ba;
    ba.append(expression);      // 把QString转换成QByteArray
    strcpy(opt, ba.data());      // data可以把QByteArray转换成const char*

    while (opt[i] != '\0' || s_opt.empty() != true)
    {
        // 数字
        if (opt[i] >= '0' && opt[i] <= '9')
        {
            tmp = tmp * 10 + opt[i] - '0';
            i++;
            if (opt[i] < '0' || opt[i] > '9')
            {
                s_num.push(tmp);
                tmp = 0;
            }
        }
        // 操作符
        else
        {
            if (s_opt.empty() == true ||
                    Priotity(opt[i]) > Priotity(s_opt.top()) ||
                        (s_opt.top() == '(' && opt[i] != ')'))
            {
                s_opt.push(opt[i]);
                i++;
                continue;
            }

            if (s_opt.top() == '(' && opt[i] == ')')
            {
                s_opt.pop();
                i++;
                continue;
            }

            if (Priotity(opt[i]) <= Priotity(s_opt.top()) ||
                         (opt[i] == ')' && s_opt.top() != ')') ||
                         (opt[i] == '\0' && s_opt.empty() != true))
            {
                char ch = s_opt.top();
                s_opt.pop();
                switch(ch)
                {
                case '+':
                    num2 = s_num.top();
                    s_num.pop();
                    num1 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 + num2);
                    break;
                case '-':
                    num2 = s_num.top();
                    s_num.pop();
                    num1 = s_num.top();
                    s_num.pop();
                    num3 = num1 - num2;
                    s_num.push(num1 - num2);
                    break;
                case '*':
                    num2 = s_num.top();
                    s_num.pop();
                    num1 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 * num2);
                    break;
                case '/':
                    num2 = s_num.top();
                    s_num.pop();
                    num1 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 / num2);
                    break;
                }
            }
            else
            {
                QMessageBox::warning(this, "警告", "请输入正确格式");
                expression.clear();
                continue;
            }
        }
    }
//    ui -> mainLineEdit -> setText(QString::number(s_num.top()));
//    expression.clear();

    expression += QString::number(s_num.top());
    ui -> mainLineEdit -> setText(expression);
}


int Widget::Priotity(char ch)
{
    switch(ch)
    {
    case '(':
        return 3;
        break;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

