#ifndef STYLES_HPP
#define STYLES_HPP

#include <QString>

extern const QString white_btn_style = "QPushButton{"
                                 "   background-color:white;"
                                 "   color:white;"
                                 "    border:1px solid #808080;"
                                 "}"
                                 "QPushButton:hover{"
                                 "    background-color: #808080;"
                                 "    color:#808080;"
                                 "    border-color:black;"
                                 "}"
                                 "QPushButton:pressed{"
                                 "    background-color:black;"
                                 "    color:black;"
                                 "    border-color:white;"
                                 "}";

extern const QString black_btn_style = "QPushButton{"
                                       "    background-color:black;"
                                       "    color:black;"
                                       "    border:1px solid #808080;"
                                       "}"
                                       "QPushButton:hover{"
                                       "    background-color: #808080;"
                                       "    color:#808080;"
                                       "    border-color:white;"
                                       "}"
                                       "QPushButton:pressed{"
                                       "    background-color:white;"
                                       "    color:white;"
                                       "    border-color:black;"
                                       "}";

#endif