package edu.harvard.cs50.notes;

import androidx.room.Database;
import androidx.room.RoomDatabase;

@Database(entities = {Note.class}, version = 1) //Note.class is a list
public abstract class NotesDatabase extends RoomDatabase {
    public abstract NoteDao noteDao(); //abstract is like an interface and class. smth that is implemented by somebody else, not myself
} //Room library will write some code for us when u use abstract