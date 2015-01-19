#include "glscreen.h"
//http://www.robot-home.it/blog/en/software/tutorial-opencv-qt-opengl-widget-per-visualizzare-immagini-da-opencv-in-una-gui-con-qt/

GLScreen::GLScreen(QWidget *parent) :
    QGLWidget(parent)
{


}


void GLScreen::initializeGL()
{
    makeCurrent();
    qglClearColor(mBgColor.darker());

}



void GLScreen::paintGL()
{
    makeCurrent();

       if( !mSceneChanged )
          return;

       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       renderImage();

       mSceneChanged = false;
       qDebug("Running paint" );
}

void GLScreen::resizeGL(int width, int height)
{

    makeCurrent();
      glViewport(0, 0, (GLint)width, (GLint)height);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      glOrtho(0, width, 0, height, 0, 1); // To Draw image in the center of the area

      glMatrixMode(GL_MODELVIEW);

      // ---> Scaled Image Sizes
      mOutH = width/mImgratio;
      mOutW = width;

      if(mOutH>height)
      {
         mOutW = height*mImgratio;
         mOutH = height;
      }

      emit imageSizeChanged( mOutW, mOutH );
      // < --- Scaled Image Sizes

      mPosX = (width-mOutW)/2;
      mPosY = (height-mOutH)/2;

      mSceneChanged = true;

      updateScene();

}
void GLScreen::updateScene()
{
   if( mSceneChanged && this->isVisible() )
      updateGL();
}

void GLScreen::renderImage()
{
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);

    if (!mRenderQtImg.isNull())
    {
        glLoadIdentity();

        QImage image; // the image rendered

        glPushMatrix();
        {
            int imW = mRenderQtImg.width();
            int imH = mRenderQtImg.height();

            // The image is to be resized to fit the widget?
            if( imW != this->size().width() &&
                    imH != this->size().height() )
            {

                image = mRenderQtImg.scaled( //this->size(),
                                             QSize(mOutW,mOutH),
                                             Qt::IgnoreAspectRatio,
                                             Qt::SmoothTransformation
                                             );

                qDebug( QString( "Image size: (%1x%2)").arg(imW).arg(imH).toAscii() );
            }
            else
                image = mRenderQtImg;

            // --->Centering image in draw area

            glRasterPos2i( mPosX, mPosY );
            // < --- Centering image in draw area

            imW = image.width();
            imH = image.height();

            glDrawPixels( imW, imH, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
        }
        glPopMatrix();

        // end
        glFlush();
    }
}
bool  GLScreen::showImage( QImage image )
{
    mRenderQtImg = QGLWidget::convertToGLFormat(image);

    mSceneChanged = true;

    updateScene();

    return true;
}
