#include "FbSs.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
//#include <QGLWidget>

class GraphicsView : public QGraphicsView {

public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = 0)
    	:     QGraphicsView(scene, parent) {}

protected:
    void resizeEvent(QResizeEvent *event) {
    	(void)event;
    	if ( items().size() )
    		fitInView(items().back(), Qt::KeepAspectRatio);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    FbSs w;
//    w.show();

    QGraphicsScene scene;
    GraphicsView view(&scene);
    //view.setViewport(new QGLWidget);
    //view.showFullScreen();

    const QString path("store/392492_273796626036990_100002199647684_627667_108466659_n.jpg");
    QGraphicsPixmapItem item(QPixmap(path, 0));
    scene.addItem(&item);
    view.centerOn(&item);
    view.fitInView(&item, Qt::KeepAspectRatio);

    view.show();

    return a.exec();
}
