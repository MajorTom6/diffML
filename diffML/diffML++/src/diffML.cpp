#include "inc/diffML.hpp"

diffML::diffML(){
        QSplitter*      splitter = new QSplitter;
        QWidget*        frame = new QWidget;
        QGridLayout*    grid = new QGridLayout;

        view            = new TreeView;
        filterText      = new QLineEdit;
        model           = NULL;

        setCentralWidget(splitter);

        initMenu();

        connect(filterText, &QLineEdit::textChanged, this, &diffML::update);

        frame->setLayout(grid);
        grid->addWidget(filterText);
        grid->addWidget(view);

        splitter->addWidget(frame);

        this->show();
}

void diffML::initMenu(){
        QMenu *file = menuBar()->addMenu("&File");

        QAction *open = new QAction("&Open", this);
        connect(open, &QAction::triggered, this, &diffML::open);
        file->addAction(open);

        //QMenu *edit = menuBar()->addMenu("&Edit");

        QMenu *viewMenu = menuBar()->addMenu("&View");

        QMenu *colorMenu = viewMenu->addMenu("&Color");
        QActionGroup *colorGroup = new QActionGroup(this);
        colorGroup->setExclusive(true);

        QAction *none = new QAction("&None", this);
        connect(none, &QAction::triggered, this, [this]{diffML::setColorState(NONE);});
        none->setCheckable(true);
        none->setChecked(true);
        colorGroup->addAction(none);
        colorMenu->addAction(none);

        QAction *hier = new QAction("&Hierarchy", this);
        connect(hier, &QAction::triggered, this, [this]{diffML::setColorState(HIERARCHY);});
        hier->setCheckable(true);
        colorGroup->addAction(hier);
        colorMenu->addAction(hier);
        
        //QMenu *help = menuBar()->addMenu("&Help");
}

void diffML::open(){
        QFileDialog FileDialog;
        QString path = FileDialog.getOpenFileName(this);

        model = new TreeModel(path);

        filter = new Filter(this);

        filter->setSourceModel(model);

        view->setModel(filter);
}

void diffML::setColorState(int colorState){
        if (model){
                model->setColorState(colorState);
        } 
}

void diffML::update(){
        QString text(filterText->text());
        filter->setFilterWildcard(text);
}
