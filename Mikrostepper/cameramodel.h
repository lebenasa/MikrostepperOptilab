#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <QAbstractListModel>

class CameraModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
	Q_PROPERTY(int cols READ cols NOTIFY colsChanged)
	int m_row, m_col;
    std::vector<bool> m_selected, m_hasImage, m_highlight;
    std::vector<QImage> m_buffer;
	QStringList m_files;
	QString m_saveDir;
public:
	enum CameraRole {
		BufferRole = Qt::UserRole + 1,
		SelectedRole,
        HighlightRole
	};
    CameraModel(const QSize& size, QObject *parent = 0);
	~CameraModel();

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex& index) const;

	int rows() const;
	int cols() const;
	QPoint selectedCell() const;
    std::vector<QPoint> selectedCells() const;

	// Convert 1D index to 2D index e.g. 11 -> 1x1
	QPoint indexToPoint(int index) const;
	// Convert 2D index to 1D index e.g. 1x1 -> 11
	int pointToIndex(const QPoint& point) const;

	// Get empty cell index based on filled cell position
	std::vector<QPoint> autoFill() const;
	// Fill empty cell from selected range
    std::vector<QPoint> boxFill() const;

public slots:
	// Client calculate correct row and column, size is cell size in pixel
	// NOTE: it will reset all data in model
	void initModel(int row, int col);

	// Set all images in buffer to 1x1 black image
	void clearBuffers();
    void clearSelectedBuffers();
	void clearBuffersAt(const QPoint &index);
	// Client choose where to update buffer according to stepper position
	void updateBuffer(const QImage &buffer, const QPoint &index);

    // Save image to file
    void saveBuffers(const QUrl& baseDir);
    void saveSelectedBuffers(const QUrl& baseDir);

	void toggleGigapan(bool t);
	void runGigapan();

	// Clear selection
	void clearSelection();
	// Select a cell
	void select(const QPoint &index);
    void multiselect(const QPoint& tl, const QPoint& br);
    void invertSelection();
    
    // Highlight a cell
    void highlight(const QPoint& index);
    void unhighlight();

    void shiftData(const QSize& shift);

    int selectedCount();

    void selectUp();
    void selectRight();
    void selectDown();
    void selectLeft();

protected:
	QHash<int, QByteArray> roleNames() const;

private:
	void saveBuffersPrivate(const QUrl& baseDir, std::function<bool(size_t)> comp);

signals :
	void rowsChanged(int row);
	void colsChanged(int col);
    void saveCompleted();
};

#endif // CAMERAMODEL_H
