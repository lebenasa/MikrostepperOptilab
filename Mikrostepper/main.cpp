#include "stdafx.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "lebenwindow.h"

#include "camera.h"
#include "stepper.h"
#include "serialcapture.h"
#include "optilabviewer.h"
#include "atlascapture.h"
#include "appsettings.h"
#include "steppernavigator.h"
#include "cameracontrol.h"
#include "autofocus.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	qmlRegisterType<LebenWindow>("Leben.Asa", 1, 0, "LebenWindow");
	qmlRegisterType<QuickCam>("QuickCam", 1, 0, "CameraItem");

    AppSettings settings;
	settings.updateCNCSettings();
    ToupCamera camera;
	//if (!camera.isAvailable()) {
	//	return 0;
	//}

	vector<unique_ptr<CamProp>> vprop;
	if (camera.isAvailable())
		vprop.emplace_back(new ToupCameraProp(camera.wrapper()));
	else
		vprop.emplace_back(new NullCamProp(&camera));
    OptilabViewer ov(&camera);
    QQmlApplicationEngine engine(&camera);
    auto ctx = engine.rootContext();
    ctx->setContextProperty("appsettings", &settings);
    ctx->setContextProperty("camera", &camera);
    ctx->setContextProperty("optilab", &ov);
    ctx->setContextProperty("camprop", vprop.at(0).get());

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
