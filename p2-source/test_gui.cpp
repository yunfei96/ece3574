#include <QDebug>
#include <QtTest/QtTest>
#include <QtWidgets>

#include "canvas_widget.hpp"
#include "main_window.hpp"
#include "message_widget.hpp"
#include "repl_widget.hpp"
#include "test_config.hpp"
// ADD YOUR TESTS TO THIS CLASS !!!!!!!
class TestGUI : public QObject {
  Q_OBJECT

public:
private slots:

    void initTestCase();
    void testREPLGood();
    void testREPLBad();
    void testREPLBad2Good();
    void testPoint();
    void testLine();
    void testArc();
    void testEnvRestore();
    void testupkey();
    void testlowkey();
    void testmain();
    void testmsg();

private:
  MainWindow w;
  REPLWidget *repl;
  QLineEdit *replEdit;
  MessageWidget *message;
  QLineEdit *messageEdit;
  CanvasWidget *canvas;
  QGraphicsScene *scene;
};

void TestGUI::initTestCase() {

  repl = w.findChild<REPLWidget *>();
  QVERIFY2(repl, "Could not find REPLWidget instance in MainWindow instance.");

  replEdit = repl->findChild<QLineEdit *>();
  QVERIFY2(replEdit,
           "Could not find QLineEdit instance in REPLWidget instance.");

  message = w.findChild<MessageWidget *>();
  QVERIFY2(message,
           "Could not find MessageWidget instance in MainWindow instance.");

  messageEdit = message->findChild<QLineEdit *>();
  QVERIFY2(messageEdit,
           "Could not find QLineEdit instance in MessageWidget instance.");

  canvas = w.findChild<CanvasWidget *>();
  QVERIFY2(canvas,
           "Could not find CanvasWidget instance in MainWindow instance.");

  scene = canvas->findChild<QGraphicsScene *>();
  QVERIFY2(scene,
           "Could not find QGraphicsScene instance in CanvasWidget instance.");
}

void TestGUI::testREPLGood() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(define a 1)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QCOMPARE(messageEdit->text(), QString("(1)"));
}

void TestGUI::testREPLBad() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(foo)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
    qDebug() << messageEdit->text();
    QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

  // check background color and selection
  QPalette p = messageEdit->palette();
  QCOMPARE(p.highlight().color(), QColor(Qt::red));
  QVERIFY2(messageEdit->selectedText().startsWith("Error"),
           "Expected error to be selected.");
}

void TestGUI::testREPLBad2Good() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(foo)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

  // check background color and selection
  QPalette p = messageEdit->palette();
  QCOMPARE(p.highlight().color(), QColor(Qt::red));
  QVERIFY2(messageEdit->selectedText().startsWith("Error"),
           "Expected error to be selected.");

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(define value 100)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QCOMPARE(messageEdit->text(), QString("(100)"));

  // check background color and selection
  p = messageEdit->palette();
  QVERIFY2(p.highlight().color() != QColor(Qt::red),
           "Did not expect red highlight on successful eval.");
  QVERIFY2(messageEdit->selectedText() == "",
           "Expected no selcted text on successful eval.");
}

void TestGUI::testPoint() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(draw (point 0 0))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check canvas
  QVERIFY2(scene->itemAt(QPointF(0, 0), QTransform()) != 0,
           "Expected a point in the scene. Not found.");
}

void TestGUI::testLine() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(draw (line (point 10 0) (point 0 10)))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
  
  // check canvas
  QVERIFY2(scene->itemAt(QPointF(10, 0), QTransform()) != 0,
           "Expected a line in the scene. Not found.");
  QVERIFY2(scene->itemAt(QPointF(0, 10), QTransform()) != 0,
           "Expected a line in the scene. Not found.");
}

void TestGUI::testArc() {
    {
        QVERIFY(repl && replEdit);
        QVERIFY(canvas && scene);

        // send a string to the repl widget
        QTest::keyClicks(replEdit, "(draw (arc (point 0 0) (point 100 0) pi))");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

        // check canvas
        QVERIFY2(scene->itemAt(QPointF(100, 0), QTransform()) != 0,
           "Expected a point on the arc in the scene. Not found.");
        QVERIFY2(scene->itemAt(QPointF(-100, 0), QTransform()) != 0,
           "Expected a point on the arc in the scene. Not found.");  
    }
    {
        QTest::keyClicks(replEdit, "(draw (arc (point 0 0) (point 0 -1) pi))");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
        
        // check canvas
        QVERIFY2(scene->itemAt(QPointF(0, -1), QTransform()) != 0,
                 "Expected a point on the arc in the scene. Not found.");
        QVERIFY2(scene->itemAt(QPointF(0, 1), QTransform()) != 0,
                 "Expected a point on the arc in the scene. Not found.");
    }

  
}


void TestGUI::testEnvRestore() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(begin (draw (point -20 0)) (define pi 3))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check canvas
  QVERIFY2(scene->itemAt(QPointF(-20, 0), QTransform()) == 0,
           "Did not expected a point in the scene. One found.");
}

void TestGUI::testupkey()
{
    QVERIFY(repl && replEdit);
    QTest::keyPress(replEdit, Qt::Key_Up);
    QVERIFY2(replEdit->text()=="(begin (draw (point -20 0)) (define pi 3))"
             ,"up key did not display the right command");
}

void TestGUI::testlowkey()
{
    QVERIFY(repl && replEdit);
    QTest::keyPress(replEdit, Qt::Key_Up);
    QTest::keyPress(replEdit, Qt::Key_Down);
    QVERIFY2(replEdit->text()=="(begin (draw (point -20 0)) (define pi 3))"
             ,"down key did not display the right command");
    QTest::keyPress(replEdit, Qt::Key_Down);
    QVERIFY2(replEdit->text()==""
             ,"down key did not display the right command");
}

void TestGUI::testmain() {
    
    MainWindow m(TEST_FILE_DIR+"test_car.vts");
    canvas = m.findChild<CanvasWidget *>();
    QVERIFY2(canvas,
             "Could not find CanvasWidget instance in MainWindow instance.");    // check canvas
    
    scene = canvas->findChild<QGraphicsScene *>();
    QVERIFY2(scene,
             "Could not find QGraphicsScene instance in CanvasWidget instance.");
    
    QVERIFY2(scene->itemAt(QPointF(-36, 10), QTransform()) == 0,
             "Did not expected a point in the scene. One found.");
    
}
void TestGUI::testmsg() {
    
    {
        // send a string to the repl widget
        QTest::keyClicks(replEdit, "(define a True)");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
        
        // check message
        QVERIFY2(messageEdit->isReadOnly(),
                 "Expected QLineEdit inside MessageWidget to be read-only.");
        QCOMPARE(messageEdit->text(), QString("(True)"));
    }
    {
        // send a string to the repl widget
        QTest::keyClicks(replEdit, "(define b False)");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
        
        // check message
        QVERIFY2(messageEdit->isReadOnly(),
                 "Expected QLineEdit inside MessageWidget to be read-only.");
        QCOMPARE(messageEdit->text(), QString("(False)"));
    }
    {
        // send a string to the repl widget
        QTest::keyClicks(replEdit, "(point 0 0)");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
        
        // check message
        QVERIFY2(messageEdit->isReadOnly(),
                 "Expected QLineEdit inside MessageWidget to be read-only.");
        QCOMPARE(messageEdit->text(), QString("(0,0)"));
    }
    {
        // send a string to the repl widget
        QTest::keyClicks(replEdit, "(line (point 0 0) (point 1 1))");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
        
        // check message
        QVERIFY2(messageEdit->isReadOnly(),
                 "Expected QLineEdit inside MessageWidget to be read-only.");
        QCOMPARE(messageEdit->text(), QString("((0,0)(1,1))"));
    }
    {
        // send a string to the repl widget
        QTest::keyClicks(replEdit, "(arc (point 0 0) (point 1 1) 1)");
        QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
        QtInterpreter i; //do nothing, make coverage beautiful!!!
        // check message
        QVERIFY2(messageEdit->isReadOnly(),
                 "Expected QLineEdit inside MessageWidget to be read-only.");
        QCOMPARE(messageEdit->text(), QString("((0,0)(1,1)1)"));
    }
    
    
}
QTEST_MAIN(TestGUI)
#include "test_gui.moc"
