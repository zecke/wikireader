/*
 * Wiki Handling Tool
 *
 * Copyright (C) 2008, 2009 Openmoko Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ExtractArticleUrl.h"

#include <QTextStream>

ExtractArticleUrl::ExtractArticleUrl(const QString& outputFile)
    : FileOutputArticleHandler(outputFile)
{}

void ExtractArticleUrl::handleArticle(const Article& article)
{
    if (article.isRedirect())
        return;

    /* the secret of our class... what to hide */
    if (article.title().title().startsWith("Image:")
        || article.title().title().startsWith("Template:")
        || article.title().title().startsWith("Category:")
        || article.title().title().startsWith("Wikipedia:")
        || article.title().title().startsWith("Talk:")
        || article.title().title().startsWith("Special:")
        || article.title().title().startsWith("Portal:")
        || article.title().title().startsWith("MediaWiki:")
        || article.title().title().startsWith("Help:"))
        return;


    QString title = article.title().title();
    title = title.replace(" ", "_");
    title = title.replace("%", "%25");

    QTextStream stream(&m_file);
    stream << article.hash() << " " << "\%SETUP\%/" + title << endl;
}
