#include <QInputDialog>
#include <QWidget>
#include <QComboBox>

#include "main_window.hpp"

MainWindow::MainWindow() {
    auto* central = new QWidget;
    auto* main_layout = new QHBoxLayout;

    auto* left_panel = new QVBoxLayout;
    auto* type_box = new QComboBox;
    type_box->addItem("array");
    type_box->addItem("list");

    auto* create_button = new QPushButton("create");
    sequence_list = new QListWidget;

    left_panel->addWidget(type_box);
    left_panel->addWidget(create_button);
    left_panel->addWidget(sequence_list);

    workspace = new QWidget;
    workspace->hide();

    auto* right_layout = new QVBoxLayout;
    auto* buttons_layout = new QHBoxLayout;

    input = new QLineEdit;

    sequence_controls = new QWidget;
    element_controls = new QWidget;
    sequence_controls->hide();
    element_controls->hide();
    auto* sequence_layout = new QHBoxLayout;
    auto* element_controls_layout = new QHBoxLayout;

    auto* append_button = new QPushButton("append");
    auto* prepend_button = new QPushButton("prepend");
    auto* remove_button = new QPushButton("remove");
    auto* delete_button = new QPushButton("delete seq");
    auto* edit_button = new QPushButton("edit");

    buttons_layout->addWidget(input);
    buttons_layout->addWidget(sequence_controls);
    buttons_layout->addWidget(element_controls);
    sequence_layout->addWidget(append_button);
    sequence_layout->addWidget(prepend_button);
    sequence_layout->addWidget(delete_button);
    element_controls_layout->addWidget(remove_button);
    element_controls_layout->addWidget(edit_button);

    sequence_controls->setLayout(sequence_layout);
    element_controls->setLayout(element_controls_layout);

    elements_layout = new QHBoxLayout;
    elements_layout->setSpacing(10);

    right_layout->addLayout(buttons_layout);
    right_layout->addLayout(elements_layout);
    workspace->setLayout(right_layout);

    main_layout->addLayout(left_panel, 1);
    main_layout->addWidget(workspace, 4);
    central->setLayout(main_layout);
    setCentralWidget(central);

    connect(create_button, &QPushButton::clicked, [this, type_box]() {
        auto type = type_box->currentText();
        if (type == "array") create_array_sequence();
        else if (type == "list") create_list_sequence();
    });
    connect(sequence_list, &QListWidget::currentRowChanged, [this]() {
        selected_element = -1;
        element_controls->hide();
        sequence_controls->show();
        redraw_workspace();
    });

    connect(append_button, &QPushButton::clicked, [this]() {
        auto index = sequence_list->currentRow();
        if (index < 0) return;

        bool ok;
        int value = input->text().toInt(&ok);
        if (!ok) return;

        sequences[index]->append(value);
        redraw_workspace();
    });

    connect(prepend_button, &QPushButton::clicked, [this]() {
        auto index = sequence_list->currentRow();
        if (index < 0) return;

        bool ok;
        int value = input->text().toInt(&ok);

        if (!ok) return;

        sequences[index]->prepend(value);
        redraw_workspace();
    });

    connect(remove_button, &QPushButton::clicked, [this]() {
        auto seq_index = sequence_list->currentRow();

        if (seq_index < 0 || selected_element < 0) return;

        sequences[seq_index]->remove(selected_element);
        if (selected_element > -1) selected_element--;
        redraw_workspace();
    });

    connect(delete_button, &QPushButton::clicked, [this]() {
        auto index = sequence_list->currentRow();
        if (index < 0) return;
        delete sequences[index];
        sequences.remove(index);
        selected_element = -1;

        redraw_sequences();
        redraw_workspace();
    });

    connect(edit_button, &QPushButton::clicked, [this]() {
        auto seq_index = sequence_list->currentRow();
        if (seq_index < 0 || selected_element < 0) return;
        bool ok;
        int value = input->text().toInt(&ok);
        if (!ok) return;

        sequences[seq_index]->set(selected_element, value);

        redraw_workspace();
    });

    resize(1200, 600);
}

MainWindow::~MainWindow() {
    for (auto seq : sequences) delete seq;
}

void MainWindow::create_array_sequence() {
    sequences.append(new array_sequence<int>);
    redraw_sequences();
}

void MainWindow::create_list_sequence() {
    sequences.append(new list_sequence<int>);
    redraw_sequences();
}

void MainWindow::redraw_sequences() {
    sequence_list->clear();
    for (auto i = 0; i < sequences.size(); ++i) {
        QString name = dynamic_cast<array_sequence<int>*>(sequences[i]) ? QString("arr seq %1").arg(i) : QString("list seq %1").arg(i);
        sequence_list->addItem(name);
    }
}

void MainWindow::redraw_workspace() {
    while (elements_layout->count()) {
        auto* item = elements_layout->takeAt(0);
        delete item->widget();
        delete item;
    }

    auto index = sequence_list->currentRow();
    if (index < 0) {
        workspace->hide();
        return;
    }
    workspace->show();
    auto* seq = sequences[index];

    for (auto i = 0; i < seq->size(); ++i) {
        auto* button = new QPushButton(QString::number((*seq)[i]));
        button->setFixedSize(60, 60);
        if (i == selected_element) button->setStyleSheet("background-color: #17B317;");

        connect(button, &QPushButton::clicked, [this, i]() {
            if (selected_element == i) {
                selected_element = -1;
                sequence_controls->show();
                element_controls->hide();
            }
            else {
                selected_element = i;
                sequence_controls->hide();
                element_controls->show();
            }
            redraw_workspace();
        });

        elements_layout->addWidget(button);
    }
}