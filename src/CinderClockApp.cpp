#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public App {
public:
    static void prepare(Settings *settings);
    void draw() override;
protected:
    int getSecondsSinceMidnight();
};

class Clock {
public:
    int getHours();
    int getMinutes();
    int getSeconds();
private:
    int getSecondsSinceMidnight();
};

int Clock::getHours()
{
    return floor(getSecondsSinceMidnight() * (300.0f / 3600.f));
}

int Clock::getMinutes()
{
    return floor(getSecondsSinceMidnight() * (30.0f / 3600.0f));
}

int Clock::getSeconds()
{
    return floor(getSecondsSinceMidnight() * (360.0f / 60.0f));
}

int Clock::getSecondsSinceMidnight()
{
    auto t = std::time(nullptr);
    auto d = std::localtime(&t);
    
    return int(d->tm_hour * 3600 + d->tm_min * 60 + d->tm_sec);
}

void CinderProjectApp::prepare(cinder::app::AppCocoaTouch::Settings *settings)
{
    settings->setTitle("Analog Clock");
    settings->setWindowSize(300, 300);
    
}

void CinderProjectApp::draw()
{
    gl::clear( Color::black() );
    
    vec2 center = 0.5f * vec2(getWindowSize());
    
    gl::color(Color::white());
    
    for( int h = 0; h < 12; ++h )
    {
        gl::pushModelView();
        
        gl::translate(center);
        gl::rotate(h * glm::radians(30.0f));
        gl::drawSolidRect(Rectf(-3, -110, 3, -90));
        
        gl::popModelView();
    }
    
    int seconds = getSecondsSinceMidnight();
    
    // long hand for minutes
    gl::pushModelView();
    gl::translate(center);
    gl::rotate(seconds * glm::radians(360.0f / 3600.0f)); // 360 degrees per 3600 seconds
    gl::drawSolidRect(Rectf(-2, -100, 2, 15));
    gl::popModelView();
    
    // short hand for hours
    gl::pushModelView();
    gl::translate(center);
    gl::rotate(seconds * glm::radians(30.0f / 3600.0f)); // 30 degrees per 3600 seconds
    gl::drawSolidRect(Rectf(-2, -60, 2, 15));
    gl::popModelView();
    
    gl::color(Color(1, 0, 0));
    
    // seconds hand
    gl::pushModelView();
    gl::translate(center);
    gl::rotate(seconds * glm::radians(360.0f / 60.0f)); // 360 degrees per 60 seconds
    gl::drawSolidRect(Rectf(-2, -100, 1, 15));
    gl::drawSolidCircle(vec2(0), 6, 24);
    gl::popModelView();
    
}


int CinderProjectApp::getSecondsSinceMidnight()
{
    auto t = std::time(nullptr);
    auto d = std::localtime(&t);
    
    return int(d->tm_hour * 3600 + d->tm_min * 60 + d->tm_sec);
}

CINDER_APP( CinderProjectApp, RendererGl(RendererGl::Options().msaa(16)), &CinderProjectApp::prepare )
