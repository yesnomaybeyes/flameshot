// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

#include "customuploadertool.h"
#include "customuploader.h"
#include <QPainter>

CustomUploaderTool::CustomUploaderTool(QObject *parent) : AbstractActionTool(parent) {

}

bool CustomUploaderTool::closeOnButtonPressed() const {
    return true;
}

QIcon CustomUploaderTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "cloud-upload.svg");
}
QString CustomUploaderTool::name() const {
    return tr("Image Uploader");
}

QString CustomUploaderTool::nameID() {
    return QLatin1String("");
}

QString CustomUploaderTool::description() const {
    return tr("Upload the selection to any service using custom command");
}

QWidget* CustomUploaderTool::widget() {
    return new CustomUploader(capture);
}

CaptureTool* CustomUploaderTool::copy(QObject *parent) {
    return new CustomUploaderTool(parent);
}

void CustomUploaderTool::pressed(const CaptureContext &context) {
    capture = context.selectedScreenshotArea();
    emit requestAction(REQ_CAPTURE_DONE_OK);
    emit requestAction(REQ_ADD_EXTERNAL_WIDGETS);
}
