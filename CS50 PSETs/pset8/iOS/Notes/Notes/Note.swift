import Foundation
import SQLite3

struct Note {
    var id: Int32
    var content: String
    //var deleted: Int
    
    /*init(deleted: Int = 0){
        self.deleted = deleted
    }*/
}

class NoteManager {
    var database: OpaquePointer?
    
    static let shared = NoteManager() //a singleton. use one time only -->static
    
    private init() {
    }
    
    func connect() {
        if database != nil {
            return
        }
        
        let databaseURL = try! FileManager.default.url(
            for: .documentDirectory,
            in: .userDomainMask,
            appropriateFor: nil,
            create: false
        ).appendingPathComponent("notes.sqlite")
        
        if sqlite3_open(databaseURL.path, &database) != SQLITE_OK {
            print("Error opening database")
            return
        }
        
        if sqlite3_exec(
            database, //only content column is created
            """
            CREATE TABLE IF NOT EXISTS notes (
                content TEXT
            )
            """,
            nil,
            nil,
            nil
        ) != SQLITE_OK {
            print("Error creating table: \(String(cString: sqlite3_errmsg(database)!))")
        }
    }
    
    func create() -> Int {
        connect()
        
        var statement: OpaquePointer? = nil
        if sqlite3_prepare_v2(
            database,
            "INSERT INTO notes (content) VALUES ('Write a note!')",
            -1,
            &statement,
            nil
        ) == SQLITE_OK {
            if sqlite3_step(statement) != SQLITE_DONE {
                print("Error inserting note")
            }
        }
        else {
            print("Error creating note insert statement")
        }
        
        sqlite3_finalize(statement)
        print("Create id: \(sqlite3_last_insert_rowid(database))")
        return Int(sqlite3_last_insert_rowid(database)) //everytime a new note is created, it's assigned the last insert row id
    }
    
    func deleteNotes(note: Note){
        connect()
        
        var statement: OpaquePointer? = nil
        if sqlite3_prepare_v2(
            database,
            "DELETE FROM notes WHERE content = ? AND rowid = ?", //rowid different from id. have to update rowid=id first
            -1,
            &statement,
            nil
        ) == SQLITE_OK {
            sqlite3_bind_text(statement, 1, NSString(string: note.content).utf8String, -1, nil) //corresponds to first ?
            sqlite3_bind_int(statement, 2, note.id) //corresponds to second ?
            if sqlite3_step(statement) != SQLITE_DONE {
                print("Error deleting note")
            }
        }
        else {
            print("Error deleting note from database")
        }
        
        sqlite3_finalize(statement)
       //return Int(sqlite3_last_insert_rowid(database))
        
        //getNotes()
    }
    
    func getNotes() -> [Note] {
        connect()
        
        var result: [Note] = [] //list of notes. init with empty array
        var statement: OpaquePointer? = nil
        if sqlite3_prepare_v2(database, "SELECT rowid, content FROM notes", -1, &statement, nil) == SQLITE_OK {
            while sqlite3_step(statement) == SQLITE_ROW {
                result.append(Note(
                    id: sqlite3_column_int(statement, 0), //0 is the leftmost column.
                    //overrides the int and content that was deleted
                    //sqlite3_column_int returns information about the column. assign Note.id as rowid
                    content: String(cString: sqlite3_column_text(statement, 1))//1 is the 2nd column
                    
                    //deleted: Int(sqlite3_column_int(statement, 2))
                ))
            }
        }
        //print(Note.self)
        sqlite3_finalize(statement)
        return result
    }
    
    func saveNote(note: Note) {
        connect()
        
        var statement: OpaquePointer? = nil
        if sqlite3_prepare_v2(
            database,
            "UPDATE notes SET content = ? WHERE rowid = ?",
            -1,
            &statement,
            nil
        ) == SQLITE_OK {
            sqlite3_bind_text(statement, 1, NSString(string: note.content).utf8String, -1, nil) //corresponds to first ?
            sqlite3_bind_int(statement, 2, note.id) //corresponds to second ?
            //sqlite3_bind_int(statement, 3, note.deleted)
            if sqlite3_step(statement) != SQLITE_DONE {
                print("Error saving note")
            }
        }
        else {
            print("Error creating note update statement")
        }
        
        sqlite3_finalize(statement)
    }
}
