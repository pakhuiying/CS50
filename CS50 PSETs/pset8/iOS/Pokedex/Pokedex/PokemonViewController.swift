import UIKit
//var pokedex = Pokedex.init(caught: [ : ])
//to get more information on each pokemon
class PokemonViewController: UIViewController {
    var url: String!
    //var entries: String!

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var Catch: UIButton!
    @IBOutlet var pokemonDescription: UITextView!
    @IBOutlet var pokemonImage: UIImageView!
    
    //var catchPokemon: Bool
   // var catchPokemon: [Bool] //list of booleans
    var catchPokemon = PokemonCaught.init(caught: [ : ]) //create empty dictionary

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        //clear all placeholders first
        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""
        pokemonDescription.text = ""
        
        
        loadPokemon()
        loadDescription()
        loadImage()
    }
    
    

    //var isCaught = true
    //var notCaught = "not caught"
    
    @IBAction func toggleCatch(){
        // if the button was selected, then deselect it.
        // otherwise if it was not selected, then select it.
        //catchPokemon.caught[nameLabel.text!] = Catch.isSelected
        //if selected, catchPokemon.caught = true for that pokemon
        
        /*if Catch.isSelected {
            Catch.setTitle("Release", for: .selected)
            Catch.setTitleColor(.red, for: .selected)
            //catchPokemon.caught[nameLabel.text!] = true
            //UserDefaults.standard.set(true, forKey: nameLabel.text!)
        }
        
        else {
            Catch.setTitle("Catch", for: .normal)
            Catch.setTitleColor(.green, for: .normal)
            //catchPokemon.caught[nameLabel.text!] = false
            //UserDefaults.standard.set(false, forKey: nameLabel.text!)
        }
        
        UserDefaults.standard.set(catchPokemon.caught[nameLabel.text!], forKey: nameLabel.text!)
        
        Catch.isSelected = !Catch.isSelected*/
        //UserDefaults.standard.set(Catch.isSelected, forKey: "isSaved")
        //UserDefaults.standard.set(Catch.isSelected, forKey: "isSaved")
        
        
        /*if Catch.currentTitle == "Release"
        {
            isCaught = true
        }
        
        else{
            isCaught = false
        } */
        //method will be called each time the button is pressed
        //setTitle(_ title: String?, for: UIControl.State)
        
        //isCaught = !isCaught
        //UserDefaults.standard.set(Catch.isSelected, forKey: "isSaved")
        //UserDefaults.standard.setValue
        //UserDefaults.standard.set(Catch.isSelected, forKey: nameLabel.text!)
        //UserDefaults.standard.set(isCaught, forKey: nameLabel.text!)
        if catchPokemon.caught[nameLabel.text!] == false || catchPokemon.caught[nameLabel.text!] == nil {
                
                Catch.setTitle("Release", for: .normal)
                catchPokemon.caught[nameLabel.text!] = true
                UserDefaults.standard.set(true, forKey: nameLabel.text!)
                
            }
            else{
                Catch.setTitle("Catch", for: .normal)
                catchPokemon.caught[nameLabel.text!] = false
                UserDefaults.standard.set(false, forKey: nameLabel.text!)
            }
        
            print("Button pressed \(catchPokemon.caught)")
        /*https://github.com/casualc0der/Pokedex/blob/master/Pokedex/PokemonViewController.swift*/
    }
    
    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                //let species = try JSONDecoder().decode(PokemonSpecies.self, from: data)
                DispatchQueue.main.async {
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.nameLabel.text = self.capitalize(text: result.name)
                    self.numberLabel.text = String(format: "#%03d", result.id)
 
                    if UserDefaults.standard.bool(forKey: self.nameLabel.text!) == true {
                        
                        self.catchPokemon.caught[self.nameLabel.text!] = true
                    }
                    
                    if self.catchPokemon.caught[self.nameLabel.text!] == false || self.catchPokemon.caught[self.nameLabel.text!] == nil  {
                            
                        self.Catch.setTitle("Catch", for: .normal)
                           
                       }
                    else if self.catchPokemon.caught[self.nameLabel.text!] == true {
                            
                        self.Catch.setTitle("Release", for: .normal)

                       }
                    
                    for typeEntry in result.types {
                        if typeEntry.slot == 1 {
                            self.type1Label.text = typeEntry.type.name
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = typeEntry.type.name
                        }
                    }
                }
            }
            catch let error {
                print(error)
            }
            
        }.resume()
    }
    
    func loadImage() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }
            
            do {
                let result = try JSONDecoder().decode(PokemonSprites.self, from: data)
                DispatchQueue.main.async {
                    do {
                        let imageData = try Data(contentsOf: URL(string: result.sprites.front_default)!)
                        self.pokemonImage.image = UIImage(data: imageData)
                    }
                    
                    catch {
                        print("Unable to load data: \(error)")
                    }
                }
            }
                
            catch let error {
                print(error)
            }
        }.resume()
    }
    
    func loadDescription() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonSpecies.self, from: data)
                URLSession.shared.dataTask(with: URL(string: result.species.url)!) { (data1, response, error) in guard let data1 = data1 else {
                        return
                    }
                    
                    do {
                        let species = try JSONDecoder().decode(PokemonFlavourEntries.self, from: data1)
                        DispatchQueue.main.async{
                            //species.flavor_text_entries is a list
                            for entries in species.flavor_text_entries {
                                if entries.language.name == "en"
                                {
                                    
                                    var textInput = entries.flavor_text
                                    textInput = textInput.replacingOccurrences(of: "\n", with: " ")
                                    self.pokemonDescription.text = textInput
                                    //self.pokemonDescription.text = textInput.filter {!$0.isNewline}
                                    //self.pokemonDescription.text = entries.flavor_text
                                    break
                                }
                            }
                        }
                    }
                    
                    catch let error {
                        print(error)
                    }
                    
                }.resume()
                
            }
            catch let error {
                print(error)
            }
            
        }.resume()
    }
    
    
    
}
