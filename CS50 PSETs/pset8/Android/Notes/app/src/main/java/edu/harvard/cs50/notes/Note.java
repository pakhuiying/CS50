package edu.harvard.cs50.notes;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

@Entity(tableName = "notes") //name of table
public class Note { //2 columns: id and contents
    @PrimaryKey
    public int id; //auto-increment

    @ColumnInfo(name = "content")
    public String content;
}
