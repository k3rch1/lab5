#pragma once

#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWidget>

#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "sequence.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    array_sequence<sequence<double>*> sequences;

    QListWidget* sequence_list;

    QWidget* workspace;
    QHBoxLayout* elements_layout;

    QWidget* sequence_controls;
    QWidget* element_controls;

    QLineEdit* input;
    int selected_element = -1;

    void create_array_sequence();
    void create_list_sequence();

    void redraw_sequences();
    void redraw_workspace();
};